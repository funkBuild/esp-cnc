#include "galvanometer.h"
#include "global.h"
#include "planner.h"
#include "motion.h"

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <limits.h>

static galvanometer_context_t galvanometers[N_GALVANOMETERS];

static void galvanometer_acceleration_update(analog_motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event){
  galvanometer_context_t* axis_ctx = (galvanometer_context_t*) self->ctx;

  float t = (float)motion_ctx->ticks * ANALOG_I2S_LOOP_DT;

  axis_ctx->position = axis_ctx->initial_position + 0.5 * t * t * axis_ctx->acceleration;

  motion_ctx->channel_value[axis_ctx->idx] = axis_ctx->position / 200.0;
}

static void galvanometer_cruise_update(analog_motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event){
  galvanometer_context_t* axis_ctx = (galvanometer_context_t*) self->ctx;

  float t = (float)motion_ctx->ticks * ANALOG_I2S_LOOP_DT;

  axis_ctx->position = axis_ctx->initial_position + t * axis_ctx->velocity;

  motion_ctx->channel_value[axis_ctx->idx] = axis_ctx->position / 200.0;
}

static void galvanometer_deceleration_update(analog_motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event){
  galvanometer_context_t* axis_ctx = (galvanometer_context_t*) self->ctx;

  float t = (float)motion_ctx->ticks  * ANALOG_I2S_LOOP_DT;

  axis_ctx->position = axis_ctx->initial_position + t * axis_ctx->velocity  - 0.5 * t * t * axis_ctx->acceleration;

  motion_ctx->channel_value[axis_ctx->idx] = axis_ctx->position / 200.0;
}

static void galvanometer_motion_analog_start(analog_motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event){
  galvanometer_context_t* axis_ctx = (galvanometer_context_t*) self->ctx;

  switch(event){
    case Cruise:
      axis_ctx->initial_position = axis_ctx->position;
      break;
    case Decelerate:
      axis_ctx->initial_velocity = axis_ctx->velocity;
      axis_ctx->initial_position = axis_ctx->position;
      break;
    default: 
      break;
  };
}

static void galvanometer_motion_analog_done(analog_motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event){
  galvanometer_context_t* axis_ctx = (galvanometer_context_t*) self->ctx;

  switch(event){
    case Accelerate: {
      float t = (float)motion_ctx->ticks * ANALOG_I2S_LOOP_DT;
      axis_ctx->velocity = axis_ctx->initial_velocity + t * axis_ctx->acceleration;

      if(motion_ctx->cruise_ticks == 0 && motion_ctx->decel_ticks == 0)
        axis_ctx->position = axis_ctx->final_position;
      break;
    }
    case Cruise: {
      if(motion_ctx->decel_ticks == 0)
        axis_ctx->position = axis_ctx->final_position;
      break;
    }
    case Decelerate:{
      axis_ctx->position = axis_ctx->final_position;
      break;
    }
  };
}

static void galvanometer_motion_analog_update(analog_motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event){
  switch(event){
    case Accelerate: 
      galvanometer_acceleration_update(motion_ctx, self, event);
      break;
    case Cruise:
      galvanometer_cruise_update(motion_ctx, self, event);
      break;
    case Decelerate:
      galvanometer_deceleration_update(motion_ctx, self, event);
      break;
  };
}

static float position_update_callback(void *ctx){
  galvanometer_context_t* axis_ctx = (galvanometer_context_t*) ctx;
  return axis_ctx->position;
}

void galvanometer_analog_setup(analog_motion_ctx_t *motion_ctx){
  for(int i=0; i < N_GALVANOMETERS; i++){
    const Axis axis_idx = galvanometers[i].axis;

    if(!galvanometers[i].enabled || motion_ctx->block->axis_distance[axis_idx] == 0) continue;
    
    motion_action_t* action = analog_motion_ctx_create_action(motion_ctx);
    action->ctx = (void*) &galvanometers[i];

    galvanometers[i].acceleration = motion_ctx->block->axis_acceleration[axis_idx];
    galvanometers[i].velocity = motion_ctx->block->entry_speed * motion_ctx->block->unit_vec[axis_idx];
    galvanometers[i].initial_velocity = galvanometers[i].velocity;
    galvanometers[i].position = axis_state.position[axis_idx];
    galvanometers[i].initial_position = axis_state.position[axis_idx];
    galvanometers[i].final_position = axis_state.position[axis_idx] + motion_ctx->block->axis_distance[axis_idx];

    galvanometers[i].start_position = INT_MAX * (galvanometers[i].position / 200.0);
    galvanometers[i].int_velocity = (INT_MAX / 200.0) * galvanometers[i].acceleration;

    action->motion_update_callback = &galvanometer_motion_analog_update;
    action->motion_start_callback = &galvanometer_motion_analog_start;
    action->motion_done_callback = &galvanometer_motion_analog_done;

    register_position_callback(axis_idx, &position_update_callback, &galvanometers[i]);
  }
}

void galvanometer_init(){
  for(int i=0; i < N_GALVANOMETERS; i++){
    galvanometers[i].idx = i;
    galvanometers[i].enabled = true;
  }

  galvanometers[0].axis = X_AXIS;
  galvanometers[1].axis = Y_AXIS;
}
