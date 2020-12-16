#include "global.h"
#include "planner.h"
#include "motion.h"
#include "stepper.h"
#include "spindle.h"
#include "galvanometer.h"
#include "api/ws_api.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <limits.h>

static TaskHandle_t digital_motion_task_handle;
static TaskHandle_t analog_motion_task_handle;

static unsigned int i2s_current_sample[2] = {0, 0};
static uint32_t stepper_samples[I2S_BUFFER_LEN];
static uint32_t analog_samples[2 * I2S_BUFFER_LEN]; // Double for stereo at 32bit each

static inline unsigned int min ( unsigned int a, unsigned int b ) { return a < b ? a : b; }

static inline void forward_analog_i2s_ticks(i2s_port_t i2s_num, unsigned int ticks){
  i2s_current_sample[i2s_num] += ticks;

  while(i2s_current_sample[i2s_num] >= I2S_BUFFER_LEN){
    size_t bytes_written;

    i2s_write(i2s_num, analog_samples, 2 * I2S_BUFFER_LEN * sizeof(uint32_t), &bytes_written, portMAX_DELAY);

    for(int i=0; i < 2*I2S_BUFFER_LEN; i++)
      analog_samples[i] = 0;

    i2s_current_sample[i2s_num] -= I2S_BUFFER_LEN;
  }
}

static inline void set_analog_value(unsigned int channel, float value){
  const unsigned int offset = 2 * i2s_current_sample[ANALOG_I2S_NUM] + channel;

  analog_samples[offset] = value * INT_MAX;
}

static inline void flush_i2s(i2s_port_t i2s_num){
  size_t bytes_written;
  const unsigned int last_sample_idx = i2s_current_sample[ANALOG_I2S_NUM] - 1;

  if(i2s_num == STEPPER_I2S_NUM){
    uint32_t last_sample = stepper_samples[last_sample_idx];

    for(int i = last_sample_idx; i < I2S_BUFFER_LEN; i++)
      stepper_samples[i] = last_sample;

    i2s_write(i2s_num, stepper_samples, I2S_BUFFER_LEN * sizeof(uint32_t), &bytes_written, portMAX_DELAY);
  } else {
    uint32_t last_sample_l = stepper_samples[2 * last_sample_idx];
    uint32_t last_sample_r = stepper_samples[2 * last_sample_idx + 1];

    for(int i = last_sample_idx; i < I2S_BUFFER_LEN; i++){
      analog_samples[2*i] = last_sample_l;
      analog_samples[2*i + 1] = last_sample_r;
    }

    i2s_write(i2s_num, analog_samples, 2 * I2S_BUFFER_LEN * sizeof(uint32_t), &bytes_written, portMAX_DELAY);
  }
}

static inline void forward_i2s_ticks(i2s_port_t i2s_num, unsigned int ticks, uint32_t direction_mask){
  i2s_current_sample[i2s_num] += ticks;

  while(i2s_current_sample[i2s_num] >= I2S_BUFFER_LEN){
    size_t bytes_written;

    if(i2s_num == STEPPER_I2S_NUM){
      i2s_write(i2s_num, stepper_samples, I2S_BUFFER_LEN * sizeof(uint32_t), &bytes_written, portMAX_DELAY);

      for(int i=0; i < I2S_BUFFER_LEN; i++)
        stepper_samples[i] = direction_mask;
    } else {
      i2s_write(i2s_num, analog_samples, I2S_BUFFER_LEN * sizeof(uint32_t), &bytes_written, portMAX_DELAY);

      for(int i=0; i < I2S_BUFFER_LEN; i++)
        analog_samples[i] = direction_mask;
    }

    i2s_current_sample[i2s_num]  -= I2S_BUFFER_LEN;
  }
}

void set_i2s_bit(int offset){
  stepper_samples[i2s_current_sample[0]] |= 1 << offset;
}

void motion_ctx_free_actions(motion_ctx_t *motion_ctx){
  for(int i=0; i < MAX_ACTIONS; i++){
    if(motion_ctx->actions[i] == NULL) continue;

    free(motion_ctx->actions[i]);
    motion_ctx->actions[i] = NULL;
  }
}

motion_action_t* motion_ctx_create_action(motion_ctx_t *motion_ctx){
  for(int i=0; i < MAX_ACTIONS; i++){
    if(motion_ctx->actions[i] == NULL){
      motion_ctx->actions[i] = malloc(sizeof(motion_action_t));

      return motion_ctx->actions[i];
    };
  }

  return NULL;  // Not possible to hit this unless you using more actions than MAX_ACTIONS
}

void perform_motion_sub_block(motion_ctx_t *motion_ctx, unsigned int block_ticks, MotionEvent event){
  if(block_ticks == 0) return;

  motion_ctx->ticks = 0;
  unsigned int t_next_event = MAX_LOOP_TICKS;

  for(int i=0; i < MAX_ACTIONS; i++){
    if(motion_ctx->actions[i] == NULL) break;

    motion_ctx->actions[i]->motion_start_callback(motion_ctx, motion_ctx->actions[i], event);
    t_next_event = min(t_next_event, motion_ctx->actions[i]->t_next);
  }

  while(motion_ctx->ticks + t_next_event < block_ticks){
    motion_ctx->ticks += t_next_event;

    forward_i2s_ticks(STEPPER_I2S_NUM, t_next_event, motion_ctx->output_mask);

    unsigned int tick_delta = t_next_event;
    t_next_event = MAX_LOOP_TICKS;

    for(motion_action_t** a = motion_ctx->actions; *a != NULL; a++){
      motion_action_t* action = *a;

      action->t_next -= tick_delta;

      if(action->t_next == 0){
        action->motion_update_callback(motion_ctx, action, event);
      }

      t_next_event = min(t_next_event, action->t_next);
    }
  }

  forward_i2s_ticks(STEPPER_I2S_NUM, block_ticks - motion_ctx->ticks, motion_ctx->output_mask);


  for(motion_action_t** a = motion_ctx->actions; *a != NULL; a++){
    motion_action_t* action = *a;
    action->motion_done_callback(motion_ctx, action, event);
  }
}

static void run_i2s_digital(){
  unsigned int notif_val = 0;
  motion_ctx_t motion_ctx;
  memset(&motion_ctx, 0, sizeof(motion_ctx_t));

  while((motion_ctx.block = lock_and_pop_motion_queue())){
    //TODO: Move this outside the motion loop, probably send and event somewhere
    ws_api_send_job_line_number(motion_ctx.block->line_number);

    // wake the analog task and give it the motion block to execute
    xTaskNotify( analog_motion_task_handle, motion_ctx.block, eSetValueWithoutOverwrite );

    stepper_motion_setup(&motion_ctx);
    spindle_motion_setup(&motion_ctx);

    motion_ctx.accel_ticks = round( motion_ctx.block->accel_time * STEPPER_I2S_SAMPLE_RATE );
    motion_ctx.cruise_ticks = round( motion_ctx.block->cruise_time * STEPPER_I2S_SAMPLE_RATE );
    motion_ctx.decel_ticks = round( motion_ctx.block->decel_time * STEPPER_I2S_SAMPLE_RATE );

    perform_motion_sub_block(&motion_ctx, motion_ctx.accel_ticks, Accelerate);
    perform_motion_sub_block(&motion_ctx, motion_ctx.cruise_ticks, Cruise);
    perform_motion_sub_block(&motion_ctx, motion_ctx.decel_ticks, Decelerate);


    while(notif_val == 0){
      xTaskNotifyWait( 0x00, ULONG_MAX, &notif_val, portMAX_DELAY );
    }

    release_position_callbacks();
    motion_ctx_free_actions(&motion_ctx);
  }

  printf("motion done\n\n");

  flush_i2s(STEPPER_I2S_NUM);
  xTaskNotify( analog_motion_task_handle, NULL, eSetValueWithoutOverwrite );

//  {
//    char tmp[100];
//    vTaskGetRunTimeStats( tmp );
//    printf("%s\n", tmp);
//  }
};




static void digital_motion_task( void * pvParameters )
{
  i2s_config_t i2s_config = {
    .mode = I2S_MODE_MASTER | I2S_MODE_TX,                                  // Only TX
    .sample_rate = STEPPER_I2S_SAMPLE_RATE,
    .bits_per_sample = 16,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,                           //2-channels
    .communication_format = I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB,
    .dma_buf_count = 6,
    .dma_buf_len = I2S_BUFFER_LEN,
    .use_apll = false,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1                                //Interrupt level 1
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = 21,
    .ws_io_num = 18,
    .data_out_num = 19,
    .data_in_num = I2S_PIN_NO_CHANGE                                               //Not used
  };

  i2s_driver_install(STEPPER_I2S_NUM, &i2s_config, 0, NULL);
  i2s_set_pin(STEPPER_I2S_NUM, &pin_config);

  while(true){
/*
    printf("Motion task sleep\n");
    vTaskSuspend( motion_task_handle );
    printf("Motion task wakeup\n");
*/

    //TODO: convert this to an idle event loop
    while(is_motion_queue_empty()){
//      vTaskDelay(1000 / portTICK_PERIOD_MS);
      forward_i2s_ticks(STEPPER_I2S_NUM, 1024, 0);
    }
    printf("motion run\n");
    run_i2s_digital();
  };
}

void analog_motion_ctx_free_actions(analog_motion_ctx_t *motion_ctx){
  for(int i=0; i < MAX_ANALOG_ACTIONS; i++){
    if(motion_ctx->actions[i] == NULL) continue;

    free(motion_ctx->actions[i]);
    motion_ctx->actions[i] = NULL;
  }
}

motion_action_t* analog_motion_ctx_create_action(analog_motion_ctx_t *motion_ctx){
  for(int i=0; i < MAX_ANALOG_ACTIONS; i++){
    if(motion_ctx->actions[i] == NULL){
      motion_ctx->actions[i] = malloc(sizeof(motion_action_t));
      
      return motion_ctx->actions[i];
    };
  }
  printf("MAX_ANALOG_ACTIONS exceeded\n");
  return NULL;  // Not possible to hit this unless you using more actions than MAX_ACTIONS
}

void perform_analog_motion_sub_block(analog_motion_ctx_t *motion_ctx, unsigned int block_ticks, MotionEvent event){
  if(block_ticks == 0) return;

  motion_ctx->ticks = 0;

  for(int i=0; i < 2; i++){
    if(motion_ctx->actions[i] == NULL) continue;

    motion_ctx->actions[i]->motion_start_callback(motion_ctx, motion_ctx->actions[i], event);
  }

  for(; motion_ctx->ticks < block_ticks; motion_ctx->ticks++){
    for(int i=0; i < 2; i++){
      if(motion_ctx->actions[i] == NULL) continue;

      motion_ctx->actions[i]->motion_update_callback(motion_ctx, motion_ctx->actions[i], event);
    }

    //printf("%f\n", motion_ctx->channel_value[0]);
    set_analog_value(0, motion_ctx->channel_value[0]);
    set_analog_value(1, motion_ctx->channel_value[1]);
    forward_analog_i2s_ticks(ANALOG_I2S_NUM, 1);
  }


  for(int i=0; i < 2; i++){
    if(motion_ctx->actions[i] == NULL) continue;
    motion_ctx->actions[i]->motion_done_callback(motion_ctx, motion_ctx->actions[i], event);
  }
}

static void run_i2s_analog(){
  analog_motion_ctx_t motion_ctx;
  memset(&motion_ctx, 0, sizeof(analog_motion_ctx_t));

  while(1){
    xTaskNotifyWait( 0x00, ULONG_MAX, &motion_ctx.block, portMAX_DELAY ); 

    if(motion_ctx.block == NULL){
      printf("idle block received\n");
      flush_i2s(ANALOG_I2S_NUM);

      //TODO: finish and push the current I2S buffer. Test if we need to push additional blocks to make sure idle state is consistent
    } else {
      //printf("motion block received\n");

      spindle_analog_setup(&motion_ctx);
      galvanometer_analog_setup(&motion_ctx);

      motion_ctx.accel_ticks = round( motion_ctx.block->accel_time * ANALOG_I2S_SAMPLE_RATE );
      motion_ctx.cruise_ticks = round( motion_ctx.block->cruise_time * ANALOG_I2S_SAMPLE_RATE );
      motion_ctx.decel_ticks = round( motion_ctx.block->decel_time * ANALOG_I2S_SAMPLE_RATE );

      perform_analog_motion_sub_block(&motion_ctx, motion_ctx.accel_ticks, Accelerate);
      perform_analog_motion_sub_block(&motion_ctx, motion_ctx.cruise_ticks, Cruise);
      perform_analog_motion_sub_block(&motion_ctx, motion_ctx.decel_ticks, Decelerate);

      analog_motion_ctx_free_actions(&motion_ctx);

      xTaskNotify( digital_motion_task_handle, 0x1234, eSetValueWithOverwrite );
    }
  }
};

static void analog_motion_task( void * pvParameters )
{
  i2s_config_t i2s_config = {
    .mode = I2S_MODE_MASTER | I2S_MODE_TX,                                  // Only TX
    .sample_rate = ANALOG_I2S_SAMPLE_RATE,
    .bits_per_sample = 32,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,                           //2-channels
    .communication_format = I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB,
    .dma_buf_count = 6,
    .dma_buf_len = I2S_BUFFER_LEN,
    .use_apll = false,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1                                //Interrupt level 1
  };

  i2s_pin_config_t pin_config = {  //TODO: Set pinout for analog i2s
    .bck_io_num = 27,
    .ws_io_num = 25,
    .data_out_num = 26,
    .data_in_num = I2S_PIN_NO_CHANGE                                               //Not used
  };

  i2s_driver_install(ANALOG_I2S_NUM, &i2s_config, 0, NULL);
  i2s_set_pin(ANALOG_I2S_NUM, &pin_config);

  while(true){
    run_i2s_analog();
  };
}

void motion_init(){
  // TODO: zero i2s  buffer
  spindle_init();

  xTaskCreate( digital_motion_task, "digital_motion_task", 4096, NULL, tskIDLE_PRIORITY, &digital_motion_task_handle );
  xTaskCreate( analog_motion_task, "analog_motion_task", 4096, NULL, tskIDLE_PRIORITY, &analog_motion_task_handle );
}

void motion_wakeup(){
  vTaskResume( digital_motion_task_handle );
}
