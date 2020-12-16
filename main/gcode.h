#pragma once

#include "global.h"

#define GCODE_N_AXIS 10

typedef struct {
  float position[GCODE_N_AXIS];
  float feed_rate;
  bool absolute_positioning;
} State;

typedef enum {
  GCODE_OK = 0,
  GCODE_INVALID_CHARACTER,
  GCODE_INVALID_AXIS
} gcode_err_t;

typedef struct {
  char code;
  double value;
  bool valid;
} Statement;


typedef struct {
  char type;
  uint8_t code;
  float axis_value[GCODE_N_AXIS];
  float parameter_value[GCODE_N_AXIS];
  unsigned int axis_value_mask;
  unsigned int parameter_value_mask;
  unsigned int line_number;
} GcodeCommand;

typedef struct {
  GcodeCommand *current_command;
  Statement *current_statement;
  char val_str[16];
  bool reached_comment;

  unsigned int line_number;
  unsigned int char_number;
} GcodeStreamContext;

gcode_err_t gcode_process_buffer(GcodeStreamContext* ctx, char *buffer, unsigned int len);



