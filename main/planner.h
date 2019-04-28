#pragma once

#define JUNCTION_DEVIATION 0.005   // TODO: Put this in a settings object
#define MINIMUM_JUNCTION_SPEED 0.0 // (mm/sec)
#define MAXIMUM_JUNCTION_SPEED 1.0E+38

#include "global.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct plan_block_t {
  float axis_distance[N_AXIS];
  float axis_acceleration[N_AXIS];
  float axis_velocity[N_AXIS];
  float axis_entry_velocity[N_AXIS];
  float unit_vec[N_AXIS];

  float distance;
  float acceleration;
  float velocity;

  float entry_speed;
  float exit_speed;
  float max_entry_speed;
  float max_junction_speed;   // Refers to the function at the start of this block
  float max_feedrate;

  float rapid_rate;           // Axis-limit adjusted maximum rate for this block direction in (mm/min)
  float programmed_rate;      // Programmed rate of this block (mm/min).
  float spindle_speed;        // Block spindle speed

  // Stuff I've added
  struct plan_block_t *next;
  struct plan_block_t *prev;

  float accel_time;
  float cruise_time;
  float decel_time;

  bool planned;
  bool running;
} plan_block_t;

extern plan_block_t *queue_head;

void add_motion_block(float* distance, float programmed_rate);
void reverse_plan();
void forward_plan();
void print_plan();
plan_block_t* lock_and_pop_motion_queue();
void planner_init();
void forward_plan_all();
bool is_motion_queue_empty();
