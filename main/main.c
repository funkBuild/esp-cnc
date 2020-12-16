#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "esp_spiffs.h"
#include "esp_log.h"


#include "motion.h"
#include "gcode.h"
#include "planner.h"
#include "motion.h"
#include "web.h"
#include "settings.h"
#include "sd_card.h"

#include <string.h>

static esp_err_t event_handler(void *ctx, system_event_t *event)
{
  switch(event->event_id) {
  case SYSTEM_EVENT_STA_GOT_IP:
    ESP_LOGI("WIFI", "WiFi Connected");
    break;
  case SYSTEM_EVENT_STA_DISCONNECTED:
    ESP_LOGI("WIFI", "WiFi Disconnected");

    esp_wifi_connect();
    break;
  default:
    break;
  }
  return ESP_OK;
}

static void nvs_init(){
  esp_err_t err = nvs_flash_init();

  if (err != ESP_OK) {
    // NVS partition has an issue
    ESP_ERROR_CHECK(nvs_flash_erase());
    ESP_ERROR_CHECK(nvs_flash_init());
  }
}

static void init_spiffs(){
  printf("Initializing SPIFFS\n");

  esp_vfs_spiffs_conf_t conf = {
    .base_path = "/spiffs",
    .partition_label = NULL,
    .max_files = 5,
    .format_if_mount_failed = false
  };

  esp_err_t ret = esp_vfs_spiffs_register(&conf);

  if (ret != ESP_OK) {
    if (ret == ESP_FAIL) {
      printf("Failed to mount or format filesystem\n");
    } else if (ret == ESP_ERR_NOT_FOUND) {
      printf("Failed to find SPIFFS partition\n");
    } else {
      printf("Failed to initialize SPIFFS\n");
    }
    //return;
  }

  if(esp_spiffs_mounted(NULL)){
    printf("SPIFFS is mounted\n");
  } else {
    printf("SPIFFS isn't mounted\n");
  }
}

static void start_wifi(){
  ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
  ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
  ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
  wifi_config_t sta_config = {
    .sta = {
      .ssid = "WiFi",
      .password = "SpasticSeagull",
      .bssid_set = false
    }
  };
  ESP_ERROR_CHECK( esp_wifi_set_config(WIFI_IF_STA, &sta_config) );
  ESP_ERROR_CHECK( esp_wifi_start() );
  ESP_ERROR_CHECK( esp_wifi_connect() );
}

void app_main(void)
{
  nvs_init();
  tcpip_adapter_init();
  esp_timer_init();

  global_init();
  settings_fetch_all();

  planner_init();
  motion_init();
  sd_card_init();
  web_init();

  start_wifi();
/*
    vTaskDelay(10000 / portTICK_PERIOD_MS);

  float distances[N_AXIS] = {100.0, 100.0, 100.0, 0, 0, 0, 0, 0, 0};

  for(int i = 0; i < 1; i++)
    add_motion_block(distances, 10);

*/
  while(1){
    printf("Free memory: %d bytes\n", esp_get_free_heap_size());
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  };

}
