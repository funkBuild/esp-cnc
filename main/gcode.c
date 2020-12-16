#include "global.h"
#include "planner.h"
#include "gcode.h"

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

const char *AXIS_MAPPING = "xyzabcuvefwijkst";


static inline unsigned char tolower(unsigned char c)
{
	if (c > 64 && c < 91)
		c -= 'A'-'a';
	return c;
}

void gcode_run_command(GcodeCommand *cmd);
void gcode_run_g_command(GcodeCommand *cmd);
void gcode_run_m_command(GcodeCommand *cmd);


State gcode_state = {
  .position = { 0 },
  .feed_rate = 1000,
  .absolute_positioning = true
};

void gcode_print_command(GcodeCommand *cmd){
  printf("%c%u", cmd->type, cmd->code);

  for(int i=0; i < GCODE_N_AXIS; i++){
    const unsigned int result = (1 << i) & cmd->axis_value_mask;

    if(result != 0){
      printf(" %c%f", AXIS_MAPPING[i], cmd->axis_value[i]);
    }
  }

  for(int i=0; i < 6; i++){
    const unsigned int result = (1 << i) & cmd->parameter_value_mask;

    if(result != 0){
      printf(" %c%f", AXIS_MAPPING[i+9], cmd->parameter_value[i]);
    }
  }

  printf("\n");
}

gcode_err_t gcode_process_buffer(GcodeStreamContext* ctx, char *buffer, unsigned int len){
  char *cur_pos = buffer;

  for(char *cur_pos = buffer; cur_pos < buffer + len; cur_pos++){
    ctx->char_number++;

    if(ctx->reached_comment && *cur_pos != '\n') continue;

    const char cur_char = tolower(*cur_pos);

    switch(cur_char){
      case ' ':
        if(ctx->reached_comment)
          continue;
      case '\n':
        if(ctx->current_statement != NULL){
          ctx->current_statement->value = strtod(ctx->val_str, NULL);

          if(ctx->current_command == NULL) {
            ctx->current_command = malloc(sizeof(GcodeCommand));
            memset(ctx->current_command, 0, sizeof(GcodeCommand));

            ctx->current_command->line_number = ctx->line_number;
          }

          switch(ctx->current_statement->code){
            case 'm':
            case 'g':
              ctx->current_command->type = ctx->current_statement->code;
              ctx->current_command->code = (uint8_t)ctx->current_statement->value;
              break;
            default: {
              const char *axis_ptr = strchr(AXIS_MAPPING, tolower(ctx->current_statement->code));

              if(axis_ptr == NULL)
                return GCODE_INVALID_AXIS;

              const unsigned int offset = axis_ptr - AXIS_MAPPING;
              if(offset < GCODE_N_AXIS) {
                ctx->current_command->axis_value[offset] = ctx->current_statement->value;
                ctx->current_command->axis_value_mask |= 1 << offset;

              } else {
                const unsigned int idx = offset - GCODE_N_AXIS;
                ctx->current_command->parameter_value[idx] = ctx->current_statement->value;
                ctx->current_command->parameter_value_mask |= 1 << idx;
              }
            }
          }

          free(ctx->current_statement);
          ctx->current_statement = NULL;
          ctx->line_number++;
          ctx->char_number = 0;
        }

        if(cur_char == '\n'){
          ctx->reached_comment = false;

          // emit statement
          if(ctx->current_command != NULL){
            //gcode_print_command(ctx->current_command);
            gcode_run_command(ctx->current_command);

            free(ctx->current_command);
            ctx->current_command = NULL;
          }
        }

        break;
      case ';':
        ctx->reached_comment = true;
        continue;


      case 'a'...'z':
        if(ctx->current_statement != NULL){
          // Double letter error i.e. 'GG'
          printf("Invalid axis character. %c\n", cur_char);
          return GCODE_INVALID_CHARACTER;
        }

        ctx->current_statement = malloc(sizeof(Statement));
        ctx->current_statement->code = cur_char;
        memset(ctx->val_str, 0, 16);
        break;

      case '+':
      case '-':
      case '.':
      case '0'...'9': {
        if(ctx->current_statement == NULL){
          printf("Invalid number character. %c\n", cur_char);
          // Got number before a statement
          return GCODE_INVALID_CHARACTER;
        }

        int val_len = strlen(ctx->val_str);
        ctx->val_str[val_len] = cur_char;
      }
    }
  }

  return GCODE_OK;
}


void gcode_run_command(GcodeCommand *cmd){
  if(cmd->type == 'g')
    gcode_run_g_command(cmd);
  else if(cmd->type == 'm')
    gcode_run_m_command(cmd);
  else
    printf("%c%u not supported\n", cmd->type, cmd->code);
}

void gcode_run_g_command(GcodeCommand *cmd){
  switch(cmd->code){
    case 0:
    case 1: {
      if(cmd->axis_value_mask == 0)
        return;

      // Do linear movement
      float delta_values[GCODE_N_AXIS] = {0};

      for(int i=0; i < GCODE_N_AXIS; i++){
        const unsigned int result = (1 << i) & cmd->axis_value_mask;

        if(result != 0){
          delta_values[i] = gcode_state.absolute_positioning ? cmd->axis_value[i] - gcode_state.position[i] : cmd->axis_value[i];
          gcode_state.position[i] = gcode_state.absolute_positioning ? cmd->axis_value[i] : gcode_state.position[i] + cmd->axis_value[i];

          //printf("Linear move. Move %c by %f\n", AXIS_MAPPING[i], delta_values[i]);
        }
      }

      const unsigned int update_feedrate = 1 & cmd->parameter_value_mask;
      if(update_feedrate > 0){
        gcode_state.feed_rate = cmd->parameter_value[0];
        //printf("Update feedrate to %f\n", cmd->parameter_value[0]);
      }


      if(delta_values[0] != 0 || delta_values[1] != 0 || delta_values[2] != 0)
        add_motion_block(delta_values, gcode_state.feed_rate, cmd->line_number);

      break;
    }
    case 90:
      gcode_state.absolute_positioning = true;
      break;
    case 91:
      gcode_state.absolute_positioning = false;
      break;
    case 92:
      // G92 Coordinate System Offset
      for(int i=0; i < GCODE_N_AXIS; i++){
        const unsigned int result = (1 << i) & cmd->axis_value_mask;

        if(result != 0){
          //printf("G92. Set position of %c to %f\n", AXIS_MAPPING[i], cmd->axis_value[i]);
          gcode_state.position[i] = cmd->axis_value[i];
        }
      }
      break;
  }
}

void gcode_run_m_command(GcodeCommand *cmd){

}
