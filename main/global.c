#include "global.h"
#include "api/ws_api.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

axis_config_t axis_config[N_AXIS] = {
  {
    .identifier = "x",
    .enabled = true,
    .acceleration_limit = 100,
    .velocity_limit = 10000.0/60.0,
    .position_callback = NULL
  },
  {
    .identifier = "y",
    .enabled = true,
    .acceleration_limit = 101, 
    .velocity_limit = 10000.0/60.0,
    .position_callback = NULL
  },
  {
    .identifier = "z",
    .enabled = true,
    .acceleration_limit = 102,
    .velocity_limit = 10000.0/60.0,
    .position_callback = NULL
  },
};

axis_state_t axis_state = {
  .position = {0, 0, 0}
};

static SemaphoreHandle_t position_mutex = NULL;

// TODO: position callbacks under load are screwy
void register_position_callback(unsigned int axis_idx, float (*position_callback)(void *), void *ctx){
  xSemaphoreTake(position_mutex, portMAX_DELAY);

  axis_config[axis_idx].position_callback = position_callback;
  axis_config[axis_idx].position_callback_ctx = ctx;

  xSemaphoreGive(position_mutex);
}

void update_position(){
  xSemaphoreTake(position_mutex, portMAX_DELAY);

  for(int i=0; i < N_AXIS; i++){
    if(axis_config[i].position_callback != NULL){
      axis_state.position[i] = axis_config[i].position_callback(axis_config[i].position_callback_ctx);
      //printf("update_pos %u, %f\n", i, axis_state.position[i]);
    } 
      //printf("stale_pos %u, %f\n", i, axis_state.position[i]);
  }
  xSemaphoreGive(position_mutex);
  ws_api_send_position();
}

void release_position_callbacks(){
  update_position();
  xSemaphoreTake(position_mutex, portMAX_DELAY);

  for(int i=0; i < N_AXIS; i++){
      //printf("end_pos %u, %f\n", i, axis_state.position[i]);
    axis_config[i].position_callback = NULL;
    axis_config[i].position_callback_ctx = NULL;
      //printf("end_pos %u, %f\n", i, axis_state.position[i]);
  }

  xSemaphoreGive(position_mutex);
}

void temp_position_task(){
  while(true){
    update_position();
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

void global_init(){
  position_mutex = xSemaphoreCreateMutex();

  release_position_callbacks();

  xTaskCreate(&temp_position_task, "temp_position_task", 4096, NULL, 5, NULL);
}
