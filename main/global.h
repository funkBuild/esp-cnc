#pragma once

#define N_AXIS 9
#define N_SPINDLES 1

typedef enum Axis {
  X_AXIS = 0,
  Y_AXIS = 1,
  Z_AXIS = 2,
  A_AXIS = 3,
  B_AXIS = 4,
  C_AXIS = 5,
  U_AXIS = 6,
  V_AXIS = 7,
  W_AXIS = 8,
} Axis;

typedef struct axis_config_t {
  float acceleration_limit[N_AXIS];
  float velocity_limit[N_AXIS];

  float (*position_callback[N_AXIS])(void *);
  void* position_callback_ctx[N_AXIS];
} axis_config_t;


typedef struct axis_state_t {
  float position[N_AXIS];
} axis_state_t;

extern axis_config_t axis_config;
extern axis_state_t axis_state;

void global_init();
void release_position_callbacks();
void register_position_callback(unsigned int axis_idx, float (*position_callback)(void *), void *ctx);
