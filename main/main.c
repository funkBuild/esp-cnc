
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "sdkconfig.h"

#include "gcode.h"
#include "planner.h"
#include "motion.h"


void motion_test(void *pvParameter)
{
  esp_timer_init();
  global_init();
  planner_init();
  motion_init();

  while(true){
    int64_t start = esp_timer_get_time();

    gcode_parse_text("G1 X10 Y10 F1000", 16);


    int64_t delta_time = esp_timer_get_time() - start;

    printf("t_plan=%lld\n", delta_time);

    vTaskDelay(10000 / portTICK_PERIOD_MS);
  }
}

void app_main()
{
  xTaskCreate(&motion_test, "motion_test", 4096, NULL, 5, NULL);
}


// 500 blocks done in time=7920046, ticks=825762
// 1000 blocks done in time=7940069, ticks=830141
// 2000 blocks done in time=7990045, ticks=833211
// 
