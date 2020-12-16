#pragma once

#include "global.h"
#include <stdbool.h>

#define N_GALVANOMETERS (2)

typedef struct analog_motion_ctx_t analog_motion_ctx_t;

typedef struct galvanometer_context_t {
  unsigned int idx;

  float acceleration;
  float velocity;
  float initial_velocity;
  float position;
  float initial_position;
  float final_position;

  int start_position;
  int int_velocity;
} galvanometer_context_t;

typedef struct galvanometer_config_t {
  Axis axis;
  bool enabled;
  float width;
} galvanometer_config_t;

extern galvanometer_config_t galvanometer_config[N_GALVANOMETERS];

void galvanometer_analog_setup(analog_motion_ctx_t *motion_ctx);
