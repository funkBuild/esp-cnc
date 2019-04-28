#include "global.h"
#include "planner.h"
#include "motion.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include <math.h>
#include <float.h>
#include <stdio.h>
#include <string.h>

plan_block_t *queue_head = NULL;
static unsigned int queue_size = 0;
static SemaphoreHandle_t queue_mutex = NULL;

void planner_init()
{
  queue_mutex = xSemaphoreCreateMutex();
}

void calc_unit_vec(plan_block_t *block){
  float max = 0;
  int i;

  for(i=0; i < N_AXIS; i++){
    max = fmax(max, fabs(block->axis_distance[i]));
  }

  // Should never happen
  if(max == 0) return;

  for(i=0; i < N_AXIS; i++){
    block->unit_vec[i] = block->axis_distance[i] / max;
  }
}

float convert_delta_vector_to_unit_vector(float *vector)
{
  uint8_t idx;
  float magnitude = 0.0;
  for (idx=0; idx<N_AXIS; idx++) {
    if (vector[idx] != 0.0) {
      magnitude += vector[idx]*vector[idx];
    }
  }
  magnitude = sqrt(magnitude);
  float inv_magnitude = 1.0/magnitude;
  for (idx=0; idx<N_AXIS; idx++) { vector[idx] *= inv_magnitude; }
  return(magnitude);
}

float limit_value_by_axis_maximum(float *max_value, float *unit_vec)
{
  uint8_t idx;
  float limit_value = FLT_MAX;
  for (idx=0; idx<N_AXIS; idx++) {
    if (unit_vec[idx] != 0) {  // Avoid divide by zero.
      limit_value = fmin(limit_value,fabs(max_value[idx]/unit_vec[idx]));
    }
  }
  return(limit_value);
}

float limit_and_scale_by_axis_maximum(float *values, float *limits, float *unit_vec)
{
  uint8_t i;
  float limit_value = FLT_MAX;

  for (i=0; i < N_AXIS; i++) {
    if (unit_vec[i] != 0) {  // Avoid divide by zero.
      limit_value = fmin(
        limit_value,
        fabs(limits[i]/unit_vec[i])
      );
    }
  }

  for (i=0; i < N_AXIS; i++) {
    values[i] = limit_value * unit_vec[i];
  }

  return limit_value;
}

void add_motion_block(float* distance, float programmed_rate)
{
  while(queue_size > 500){
    vTaskDelay(10 / portTICK_PERIOD_MS);
  };

  plan_block_t *new_block = malloc(sizeof(plan_block_t));

  new_block->planned = false;
  new_block->running = false;
  new_block->next = NULL;

  for(int i=0; i < N_AXIS; i++){
    new_block->axis_distance[i] = distance[i];
  }
  new_block->distance = fmax(fabs(distance[0]), fmax(fabs(distance[1]), fabs(distance[2]))); //sqrt(x*x + y*y + z*z);

  calc_unit_vec(new_block);

  new_block->rapid_rate = limit_and_scale_by_axis_maximum(new_block->axis_velocity, axis_config.velocity_limit, new_block->unit_vec);
  new_block->acceleration = limit_and_scale_by_axis_maximum(new_block->axis_acceleration, axis_config.acceleration_limit, new_block->unit_vec);
  new_block->programmed_rate = fmin(programmed_rate, new_block->rapid_rate);   // TODO: Review this, seems weird
  new_block->max_feedrate = new_block->programmed_rate;

  xSemaphoreTake(queue_mutex, portMAX_DELAY);

  if(queue_head == NULL){
    new_block->prev = NULL;
 
    queue_head = new_block;
  } else {
    plan_block_t *current = queue_head;

    while(current->next != NULL){
      current = current->next;
    }
    
    current->next = new_block;
    new_block->prev = current;
  }

  queue_size++;

  reverse_plan();

  xSemaphoreGive(queue_mutex);

  forward_plan_all();
  motion_wakeup();
}

void calc_junction_speed(plan_block_t *current, plan_block_t *prev){
  if(prev == NULL) {
    current->max_junction_speed = MINIMUM_JUNCTION_SPEED;
    return;
  }

  // The GRBL corner algorithm - https://github.com/gnea/grbl/blob/master/grbl/planner.c#L429

  float junction_unit_vec[N_AXIS];
  float junction_cos_theta = 0.0;

  for(int i=0; i < N_AXIS; i++) {
    junction_cos_theta -= prev->unit_vec[i] * current->unit_vec[i];
    junction_unit_vec[i] = current->unit_vec[i] - prev->unit_vec[i];
  }

  // NOTE: Computed without any expensive trig, sin() or acos(), by trig half angle identity of cos(theta).
  if (junction_cos_theta > 0.999999) {
    current->max_junction_speed = MINIMUM_JUNCTION_SPEED;
  } else {
    if (junction_cos_theta < -0.999999) {
      // Junction is a straight line or 180 degrees. Junction speed is infinite.
      current->max_junction_speed = FLT_MAX;
    } else {
      convert_delta_vector_to_unit_vector(junction_unit_vec);

      float junction_acceleration = limit_value_by_axis_maximum(axis_config.acceleration_limit, junction_unit_vec);
      float sin_theta_d2 = sqrt(0.5*(1.0-junction_cos_theta)); // Trig half angle identity. Always positive.

      current->max_junction_speed = fmax(
        MINIMUM_JUNCTION_SPEED,
        sqrt((junction_acceleration * JUNCTION_DEVIATION * sin_theta_d2)/(1.0-sin_theta_d2))
      );
    }
  }
}

void reverse_plan(){
  //printf("Start reverse plan\n");
  int n = 0;
  plan_block_t *current = queue_head;
  float exit_speed;

  // Get the tail
  while(current->next != NULL){
    current = current->next;
  }


  // Iterate backwards and plan
  while(current != NULL) {
    if(current->running) break;

    if(current->next != NULL){
      exit_speed = fmin(current->programmed_rate, fmin(current->next->max_entry_speed, current->next->max_junction_speed));
      
      // If there's no change we don't need to continue re-planning
      if(current->exit_speed == exit_speed) break;

      current->planned = false; // Mark as unplanned so we know to re-do the forward plan on this block
      current->exit_speed = exit_speed;
    } else
      current->exit_speed = 0;

    current->max_entry_speed = fmin(
      current->programmed_rate,
      current->exit_speed + sqrt(2 * current->distance * current->acceleration)
    );

    calc_junction_speed(current, current->prev);
    n++;

    current = current->prev;
  }

  //printf("End reverse plan. n=%d\n", n);
}

void forward_plan_single(float current_velocity, plan_block_t *current){
  float decel_delta_v = 0, accel_delta_v = 0;
  float accel_distance = 0, decel_distance = 0;

  current->entry_speed = current_velocity;

  if(current_velocity == current->max_entry_speed){
    // Entering the block at the max speed, only cruise or de-acceleration is possible
    accel_distance = 0;

    decel_delta_v = current_velocity - current->exit_speed;
    decel_distance = pow(decel_delta_v, 2) / (2* current->acceleration) + current->exit_speed * (decel_delta_v / current->acceleration);

    // used for laser dynamic power calc
    current->max_feedrate = current_velocity;
  } else {
    accel_delta_v = current->programmed_rate - current_velocity;
    accel_distance = pow(accel_delta_v, 2) / (2* current->acceleration) + current_velocity * (accel_delta_v / current->acceleration);

    decel_delta_v = current->programmed_rate - current->exit_speed;;
    decel_distance = pow(decel_delta_v, 2) / (2* current->acceleration) + current->exit_speed * (decel_delta_v / current->acceleration);


    if(accel_distance + decel_distance > current->distance){
      // We can't reach the programmed velocity so the cruise time is zero and we need to re-caluclate

      float v_max_sqr = current->distance * current->acceleration + pow(current->exit_speed, 2) / 2 + pow(current_velocity, 2) / 2;
      float v_max = sqrt(v_max_sqr);

      // used for laser dynamic power calc
      current->max_feedrate = v_max;

      accel_delta_v = v_max - current_velocity;
      accel_distance = pow(accel_delta_v, 2) / (2* current->acceleration) + current_velocity * (accel_delta_v / current->acceleration);

      decel_delta_v = v_max - current->exit_speed;
      decel_distance = pow(decel_delta_v, 2) / (2* current->acceleration) + current->exit_speed * (decel_delta_v / current->acceleration);
    }
  }

  current->accel_time = fabs( accel_delta_v / current->acceleration );
  current->decel_time = fabs( decel_delta_v / current->acceleration );
  current->cruise_time = fabs( (current->distance - accel_distance - decel_distance) / current->programmed_rate );

  current->planned = true;
}

void forward_plan_all(){
  plan_block_t *current = queue_head;
  float current_velocity = 0;

  while(current != NULL){
    if(!current->planned)
      forward_plan_single(current_velocity, current);

    current_velocity = current->exit_speed;
    current = current->next;
  }
}

void print_plan(){
  printf("--------------\nMotion plan\n");

  plan_block_t *current = queue_head;

  while(current != NULL){
    printf("--------------\n");
    printf("entry_speed=%f\n", current->entry_speed);
    printf("max_junction_speed=%f\n", current->max_junction_speed);
    printf("max_entry_speed=%f\n", current->max_entry_speed);
    printf("distance=%f\n", current->distance);
    printf("rapid_rate=%f\n", current->rapid_rate);
    printf("programmed_rate=%f\n", current->programmed_rate);
    printf("accel_time=%f\n", current->accel_time);
    printf("cruise_time=%f\n", current->cruise_time);
    printf("decel_time=%f\n", current->decel_time);

    current = current->next;
  }
}

void print_position(){
  printf("\n");
  for(int i=0; i < N_AXIS; i++)
    printf("pos[%d]=%f\n", i, axis_state.position[i]);
}

plan_block_t* lock_and_pop_motion_queue(){
  float current_velocity = 0;

  xSemaphoreTake(queue_mutex, portMAX_DELAY);
  
  if(queue_head->running){
    plan_block_t *next = queue_head->next;
    current_velocity = queue_head->exit_speed;

    free(queue_head);
    queue_size--;

    queue_head = next;
  }

  if(queue_head){
    queue_head->prev = NULL;
    queue_head->running = true;

    if(!queue_head->planned){
      forward_plan_single(current_velocity, queue_head);
      printf("planned in wrong thread\n");
    }
  }

  xSemaphoreGive(queue_mutex);

  return queue_head;
}

bool is_motion_queue_empty(){
  return queue_head == NULL;
}


