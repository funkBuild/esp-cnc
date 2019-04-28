#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct motion_ctx_t motion_ctx_t;
typedef struct analog_motion_ctx_t analog_motion_ctx_t;

typedef enum SpindleOutputType {PWM, Analog} SpindleOutputType; 

typedef struct spindle_context_t {
  unsigned int idx;

  SpindleOutputType output_type;
  unsigned int analog_channel_idx;

  bool enabled;
  bool dynamic_power;
  unsigned int frequency;
  unsigned int max_speed;
  unsigned int speed;
  
  // private
  unsigned int count;
  unsigned int threshold;
  unsigned int max_count;

  // dynamic power
  unsigned int segment_count;       // ticks in the current segment. Used to calc power level based on how far through the segment we are
  float segment_power_start;
  float segment_power_delta;
} spindle_context_t;


void spindle_init();
void spindle_motion_setup(motion_ctx_t *motion_ctx);
void spindle_analog_setup(analog_motion_ctx_t *motion_ctx);
