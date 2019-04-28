#include "global.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

axis_config_t axis_config = {
  .acceleration_limit = {100, 100, 100},
  .velocity_limit = {10000.0/60.0, 10000/60.0, 10000/60.0}
};

axis_state_t axis_state = {
  .position = {0, 0, 0}
};

static SemaphoreHandle_t position_mutex = NULL;

void register_position_callback(unsigned int axis_idx, float (*position_callback)(void *), void *ctx){
  xSemaphoreTake(position_mutex, portMAX_DELAY);

  axis_config.position_callback[axis_idx] = position_callback;
  axis_config.position_callback_ctx[axis_idx] = ctx;

  xSemaphoreGive(position_mutex);
}

void update_position(){
  xSemaphoreTake(position_mutex, portMAX_DELAY);

  for(int i=0; i < N_AXIS; i++){
    if(axis_config.position_callback[i] != NULL){
      axis_state.position[i] = axis_config.position_callback[i](axis_config.position_callback_ctx[i]);

      printf("pos[%d]=%f\n", i, axis_state.position[i]);
    }
  }

  xSemaphoreGive(position_mutex);
}

void release_position_callbacks(){
  update_position();
  xSemaphoreTake(position_mutex, portMAX_DELAY);

  for(int i=0; i < N_AXIS; i++)
    axis_config.position_callback[i] = NULL;

  xSemaphoreGive(position_mutex);
}

void temp_position_task(){
  while(true){
    update_position();
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

void global_init(){
  position_mutex = xSemaphoreCreateMutex();

  release_position_callbacks();

  xTaskCreate(&temp_position_task, "temp_position_task", 4096, NULL, 5, NULL);
}
