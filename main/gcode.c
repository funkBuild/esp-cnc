#include "global.h"
#include "planner.h"

#include <stdio.h>

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

typedef struct {
  char code;
  double value;
  bool valid;
} Statement;

typedef struct {
  char type;
  uint8_t code;
  float position[N_AXIS];
  float feed_rate;
} GcodeCommand;

typedef struct {
  float position[N_AXIS];
  float last_feed_rate;
} State;

State current_state = {
  .position = { 0, 0, 0, 0 },
  .last_feed_rate = 1000
};

Statement gcode_parse_statement(char *text, int *char_counter){
  char *start = text + *char_counter;
  char *end;

  Statement statement;
  statement.valid = true;

  do {
    statement.code = start[0];
    start++;
  } while(statement.code == ' ');

  if(statement.code < 'A' || statement.code > 'z')
    statement.valid = false;

  statement.value = strtod(start, &end);
  *char_counter = end - text;

  return statement;  
}

bool gcode_parse(GcodeCommand *cmd, char *text, int len){
  int char_counter = 0;
  Statement statement;

  statement = gcode_parse_statement(text, &char_counter);

  if(!statement.valid)
    return false;

  cmd->type = statement.code;
  cmd->code = statement.value;

  while(char_counter < len){
    statement = gcode_parse_statement(text, &char_counter);

    if(!statement.valid)
      return false;

    switch(statement.code){
      case 'X':
        cmd->position[0] = statement.value;
        break;
      case 'Y':
        cmd->position[1] = statement.value;
        break;
      case 'Z':
        cmd->position[2] = statement.value;
        break;
      case 'E':
        cmd->position[3] = statement.value;
        break;
      case 'F':
        cmd->feed_rate = statement.value;
        current_state.last_feed_rate = cmd->feed_rate;
        break;
    }
  }

  return true;
}

void gcode_run_g_command(GcodeCommand *cmd){
  switch(cmd->code){
    case 1:
      add_motion_block(cmd->position, cmd->feed_rate);
      break;
  }
}

void gcode_run_command(GcodeCommand *cmd){
  switch(cmd->type){
    case 'G':
      gcode_run_g_command(cmd);
      break;
  }
}

void gcode_update_state(GcodeCommand *cmd){
  switch(cmd->type){
    case 'G':
      memcpy(current_state.position, cmd->position, N_AXIS * sizeof(float));
      current_state.last_feed_rate = cmd->feed_rate;
      break;
  }
}

bool gcode_parse_text(char *text, int length)
{
  GcodeCommand *cmd = malloc(sizeof(GcodeCommand));
  memcpy(cmd->position, current_state.position, N_AXIS * sizeof(float));
  cmd->feed_rate = current_state.last_feed_rate;

  if(gcode_parse(cmd, text, length)) {
    gcode_update_state(cmd);
    gcode_run_command(cmd);

    return true;
  }

  return false;
}
