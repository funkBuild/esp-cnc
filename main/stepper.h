#pragma once

#include "global.h"
#include "motion.h"
#include <stdbool.h>

#define N_STEPPERS 3

typedef struct motion_ctx_t motion_ctx_t;

typedef struct stepper_context_t {
  unsigned int idx;

  bool direction;
  unsigned int t_next;
  unsigned int steps;

  float err;
  float velocity;
  float initial_velocity;
  float initial_position;
  float position;
  float final_position;
  float step_distance;
  float acceleration;
} stepper_context_t;

typedef struct stepper_config_t {
  Axis axis;
  bool enabled; //TODO: Implement
  float steps_per_mm;
} stepper_config_t;

extern stepper_config_t stepper_config[N_STEPPERS];

void stepper_motion_update(motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event);
void stepper_motion_start(motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event);
void stepper_motion_done(motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event);
void stepper_motion_setup(motion_ctx_t *motion_ctx);
void stepper_init();
