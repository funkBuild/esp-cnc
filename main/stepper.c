#include "stepper.h"
#include "global.h"
#include "planner.h"
#include "motion.h"


#include <stdio.h>
#include <math.h>
#include <string.h>

static stepper_context_t steppers[N_STEPPERS];
stepper_config_t stepper_config[N_STEPPERS] = {
  {
    .enabled = true,
    .steps_per_mm = 400.0,
    .axis = X_AXIS
  },
  {
    .enabled = true,
    .steps_per_mm = 400.0,
    .axis = Y_AXIS
  },
  {
    .enabled = true,
    .steps_per_mm = 400.0,
    .axis = Z_AXIS
  }
  //TODO: initialize to maximum count
};

static inline float get_step_time(stepper_context_t* axis_ctx, float acceleration, float velocity, float step_distance, bool direction){
  return fabs(STEPPER_I2S_SAMPLE_RATE * (sqrt(2.0 * acceleration * step_distance + velocity * velocity) - velocity) / acceleration);
}

static inline float calc_remaining_step(stepper_context_t* axis_ctx, bool direction){
  float step_distance =  1 - fabs(fmod(axis_ctx->position, 1.0f));

  if(step_distance == 0.0f)
    return 1.0f;
  else
    return step_distance;
}


static inline void set_motor_step(int motor_num){
  set_i2s_bit(2 * (10+motor_num));
}

static inline void update_axis_position(stepper_context_t* axis_ctx, float distance){
  if(axis_ctx->direction)
    axis_ctx->position += distance;
  else
    axis_ctx->position -= distance;
}

/*
*     Acceleration
*/

static void stepper_acceleration_update(motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event, bool initial_run){
  stepper_context_t* axis_ctx = (stepper_context_t*) self->ctx;

  if(initial_run){
    axis_ctx->step_distance = calc_remaining_step(axis_ctx, axis_ctx->direction);

  } else {
    set_motor_step(axis_ctx->idx);
    update_axis_position(axis_ctx, axis_ctx->step_distance);

    axis_ctx->step_distance = 1.0f;
    axis_ctx->velocity = axis_ctx->initial_velocity + motion_ctx->ticks * STEPPER_I2S_LOOP_DT * axis_ctx->acceleration;
  }

  float t_next = get_step_time(axis_ctx, axis_ctx->acceleration, fabs(axis_ctx->velocity), axis_ctx->step_distance / stepper_config[axis_ctx->idx].steps_per_mm, axis_ctx->direction);

  self->t_next = floor(t_next);
  axis_ctx->err += (t_next - self->t_next);

  if(axis_ctx->err >= 1.0f){
    self->t_next++;
    axis_ctx->err -= 1.0f;
  }
}

void stepper_acceleration_done(motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event){
  stepper_context_t* axis_ctx = (stepper_context_t*) self->ctx;


  const float t = motion_ctx->block->accel_time;
  const float step_delta = (t * axis_ctx->initial_velocity + 0.5 * axis_ctx->acceleration * t * t) * stepper_config[axis_ctx->idx].steps_per_mm;

  //printf("Acc   Axis %d :: ticks=%d, velocity=%f, distance=%f\n", axis_ctx->idx, motion_ctx->ticks, axis_ctx->velocity, axis_ctx->position);

  if(motion_ctx->cruise_ticks == 0 && motion_ctx->decel_ticks == 0){
    //printf("pos_err=%f\n", axis_ctx->position - axis_ctx->final_position);
    axis_ctx->position = axis_ctx->final_position;
  }else
    axis_ctx->position = axis_ctx->direction ? axis_ctx->initial_position + step_delta : axis_ctx->initial_position - step_delta;

  axis_ctx->velocity = axis_ctx->initial_velocity + t * axis_ctx->acceleration;
  axis_ctx->err = 0;


}

/*
*   Cruise
*/

static void stepper_cruise_update(motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event, bool initial_run){
  stepper_context_t* axis_ctx = (stepper_context_t*) self->ctx;

  if(initial_run){
    axis_ctx->initial_position = axis_ctx->position;
    //axis_ctx->velocity = motion_ctx->block->programmed_rate * motion_ctx->block->unit_vec[axis_ctx->idx];
    axis_ctx->step_distance = calc_remaining_step(axis_ctx, axis_ctx->direction);
  } else {
    set_motor_step(axis_ctx->idx);
    update_axis_position(axis_ctx, axis_ctx->step_distance);
    axis_ctx->step_distance = 1.0f;
  }

  float t_next = fabs(STEPPER_I2S_SAMPLE_RATE * ((axis_ctx->step_distance / stepper_config[axis_ctx->idx].steps_per_mm) / axis_ctx->velocity));

  self->t_next = floor(t_next);
  axis_ctx->err += (t_next - self->t_next);

  if(axis_ctx->err >= 1.0f){
    self->t_next++;
    axis_ctx->err -= 1.0f;
  }
}

void stepper_cruise_done(motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event){
  stepper_context_t* axis_ctx = (stepper_context_t*) self->ctx;

  const float t = motion_ctx->block->cruise_time;
  const float step_delta = t * axis_ctx->velocity * stepper_config[axis_ctx->idx].steps_per_mm;

  //printf("Cruise   Axis %d :: ticks=%d, velocity=%f, distance=%f\n", axis_ctx->idx, motion_ctx->ticks, axis_ctx->velocity, axis_ctx->position);

  if(motion_ctx->decel_ticks == 0){
    //printf("cruise pos_err=%f\n", axis_ctx->position - axis_ctx->final_position);
    axis_ctx->position = axis_ctx->final_position;
  } else
    axis_ctx->position = axis_ctx->direction ? axis_ctx->initial_position + step_delta : axis_ctx->initial_position - step_delta;

  //if(axis_ctx->idx == 0)
  //  printf("i=%u, p=%f, v=%f, t=%u, a=%f\n", axis_ctx->idx, axis_ctx->position, axis_ctx->velocity, motion_ctx->ticks, axis_ctx->acceleration);

  axis_ctx->err = 0;


}

/*
*   Decelerate
*/

static void stepper_deceleration_update(motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event, bool initial_run){
  stepper_context_t* axis_ctx = (stepper_context_t*) self->ctx;

  if(initial_run){
    axis_ctx->initial_velocity = axis_ctx->velocity;
    axis_ctx->step_distance = calc_remaining_step(axis_ctx, axis_ctx->direction);

  } else {
    set_motor_step(axis_ctx->idx);
    update_axis_position(axis_ctx, axis_ctx->step_distance);

    axis_ctx->step_distance = 1.0f;
    axis_ctx->velocity = axis_ctx->initial_velocity - motion_ctx->ticks * STEPPER_I2S_LOOP_DT * axis_ctx->acceleration;

    //if(motion_ctx->ticks % 500 == 0 && axis_ctx->idx == 0)
    //  printf("i=%u, p=%f, v=%f, t=%u, a=%f\n", axis_ctx->idx, axis_ctx->position, axis_ctx->velocity, motion_ctx->ticks, axis_ctx->acceleration);
  }

  float t_next = get_step_time(axis_ctx, -1 * axis_ctx->acceleration, fabs(axis_ctx->velocity), axis_ctx->step_distance / stepper_config[axis_ctx->idx].steps_per_mm, axis_ctx->direction);

  self->t_next = floor(t_next);
  axis_ctx->err += (t_next - self->t_next);

  if(axis_ctx->err >= 1.0f){
    self->t_next++;
    axis_ctx->err -= 1.0f;
  }
}

void stepper_deceleration_done(motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event){
  stepper_context_t* axis_ctx = (stepper_context_t*) self->ctx;

  //printf("Axis %d :: ticks=%d, velocity=%f, distance=%f\n", axis_ctx->idx, motion_ctx->ticks, axis_ctx->velocity, axis_ctx->position); //axis_state.position[axis_ctx->idx]);

  axis_ctx->velocity = axis_ctx->initial_velocity - motion_ctx->block->decel_time * axis_ctx->acceleration;

  //printf("dec pos_err=%f\n", axis_ctx->position - axis_ctx->final_position);
  axis_ctx->position = axis_ctx->final_position;
}

void stepper_motion_start(motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event){
  switch(event){
    case Accelerate: 
      stepper_acceleration_update(motion_ctx, self, event, true);
      break;
    case Cruise:
      stepper_cruise_update(motion_ctx, self, event, true);
      break;
    case Decelerate:
      stepper_deceleration_update(motion_ctx, self, event, true);
      break;
  };
}

void stepper_motion_update(motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event){
  switch(event){
    case Accelerate: 
      stepper_acceleration_update(motion_ctx, self, event, false);
      break;
    case Cruise:
      stepper_cruise_update(motion_ctx, self, event, false);
      break;
    case Decelerate:
      stepper_deceleration_update(motion_ctx, self, event, false);
      break;
  };
}

void stepper_motion_done(motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event){
  switch(event){
    case Accelerate:
      stepper_acceleration_done(motion_ctx, self, event);
      break;
    case Cruise:
      stepper_cruise_done(motion_ctx, self, event);
      break;
    case Decelerate:
      stepper_deceleration_done(motion_ctx, self, event);
      break;
  };
}

static float position_update_callback(void *ctx){
  stepper_context_t* axis_ctx = (stepper_context_t*) ctx;
  
  return axis_ctx->position / stepper_config[axis_ctx->idx].steps_per_mm;
}


void stepper_motion_setup(motion_ctx_t *motion_ctx){
  for(int i=0; i < N_STEPPERS; i++){
    const Axis axis_idx = stepper_config[i].axis;

    if(motion_ctx->block->axis_distance[axis_idx] == 0) continue;

    motion_action_t* action = motion_ctx_create_action(motion_ctx);
    action->ctx = (void*) &steppers[i];

    steppers[i].idx = i;
    steppers[i].direction = motion_ctx->block->axis_distance[axis_idx] >= 0;
    steppers[i].acceleration = fabs(motion_ctx->block->axis_acceleration[axis_idx]);
    steppers[i].t_next = 0;
    steppers[i].err = 0;
    steppers[i].velocity = fabs( motion_ctx->block->entry_speed * motion_ctx->block->unit_vec[axis_idx] );
    steppers[i].initial_velocity = steppers[i].velocity;
    steppers[i].position = axis_state.position[axis_idx] * stepper_config[i].steps_per_mm;
    steppers[i].initial_position = steppers[i].position;
    steppers[i].final_position = (axis_state.position[axis_idx] + motion_ctx->block->axis_distance[axis_idx]) * stepper_config[i].steps_per_mm;

    //printf("i=%u, pos=%f, f_pos=%f\n", i, steppers[i].position, steppers[i].final_position);
    //printf("entry_velocity=%f, exit_vel=%f\n", steppers[i].velocity, fabs( motion_ctx->block->exit_speed * motion_ctx->block->unit_vec[axis_idx] ));
    //printf("accel=%f, dir=%u\n", steppers[i].acceleration, steppers[i].direction);

    // set callbacks
    action->motion_update_callback = &stepper_motion_update;
    action->motion_start_callback = &stepper_motion_start;
    action->motion_done_callback = &stepper_motion_done;

    register_position_callback(axis_idx, &position_update_callback, &steppers[i]);
  }
}
