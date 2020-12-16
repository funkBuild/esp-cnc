#pragma once

#define STEPPER_I2S_SAMPLE_RATE (280000)
#define STEPPER_I2S_LOOP_DT (1.0f/STEPPER_I2S_SAMPLE_RATE)
#define STEPPER_I2S_NUM 0

#define ANALOG_I2S_SAMPLE_RATE (48000)
#define ANALOG_I2S_LOOP_DT (1.0f/ANALOG_I2S_SAMPLE_RATE)
#define ANALOG_I2S_NUM 1

#define I2S_BUFFER_LEN 512
#define MAX_LOOP_TICKS (1073741824)
#define MAX_ACTIONS 16
#define MAX_ANALOG_ACTIONS 2

#include <stdbool.h>
#include <stdint.h>

typedef struct motion_ctx_t motion_ctx_t;
typedef struct analog_motion_ctx_t analog_motion_ctx_t;
typedef struct motion_action_t motion_action_t;
typedef struct plan_block_t plan_block_t;

typedef enum MotionEvent {Accelerate, Cruise, Decelerate} MotionEvent; 

struct motion_action_t {
  unsigned int t_next;

  void *ctx; // axis_context_t, spindle_context_t, laser_context etc.

  void (*motion_update_callback)(void* motion_ctx, motion_action_t* self, MotionEvent event);
  void (*motion_start_callback)(void* motion_ctx, motion_action_t* self, MotionEvent event);
  void (*motion_done_callback)(void* motion_ctx, motion_action_t* self, MotionEvent event);
};

struct motion_ctx_t {
  plan_block_t *block;
  
  motion_action_t* actions[MAX_ACTIONS];

  unsigned int ticks;
  uint32_t output_mask; // was direction mask
  unsigned int accel_ticks;
  unsigned int cruise_ticks;
  unsigned int decel_ticks;
};

struct analog_motion_ctx_t {
  plan_block_t *block;
  
  motion_action_t* actions[MAX_ANALOG_ACTIONS];
  float channel_value[2];
  float time;

  unsigned int ticks;
  unsigned int accel_ticks;
  unsigned int cruise_ticks;
  unsigned int decel_ticks;
};

void motion_init();
void motion_wakeup();

void set_i2s_bit(int offset);

motion_action_t* motion_ctx_create_action(motion_ctx_t *motion_ctx);
motion_action_t* analog_motion_ctx_create_action(analog_motion_ctx_t *motion_ctx);
