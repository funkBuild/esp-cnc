#pragma once

#include "global.h"
#include <stdbool.h>

#define N_GALVANOMETERS (2)

typedef struct analog_motion_ctx_t analog_motion_ctx_t;

typedef struct galvanometer_context_t {
  unsigned int idx;
  Axis axis;
  bool enabled;

  float acceleration;
  float velocity;
  float initial_velocity;
  float position;
  float initial_position;
  float final_position;

  int start_position;
  int int_velocity;
} galvanometer_context_t;

void galvanometer_analog_setup(analog_motion_ctx_t *motion_ctx);
void galvanometer_init();
