#include "settings.h"
#include "global.h"
#include "stepper.h"
#include "spindle.h"
#include "galvanometer.h"

static const char* TAG = "SETTINGS";

#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"

static void fetch_config_from_nvs(char *key, void *dest, size_t len){
  nvs_handle my_handle;
  esp_err_t err = nvs_open("config", NVS_READWRITE, &my_handle);

  if (err == ESP_OK) {
    size_t size;

    nvs_get_blob(my_handle, key, NULL, &size);

    if(size != len){
      ESP_LOGE(TAG, "Invalid or missing settings in NVS for %s. %d != %d", key, len, size);
      return;
    }

    nvs_get_blob(my_handle, key, dest, &size);

    nvs_commit(my_handle);
    nvs_close(my_handle);

    ESP_LOGI(TAG, "Fetched settings from NVS for %s", key);
  } else {
    ESP_LOGE(TAG, "Failed to fetch settings to NVS for %s", key);
  }
}

static void save_config_to_nvs(char *key, void *src, size_t len){
  nvs_handle my_handle;

  esp_err_t err = nvs_open("config", NVS_READWRITE, &my_handle);

  if (err == ESP_OK) {
    nvs_set_blob(my_handle, key, src, len);

    nvs_commit(my_handle);
    nvs_close(my_handle);

    ESP_LOGI(TAG, "Settings saved to NVS for %s", key);
  } else {
    ESP_LOGE(TAG, "Failed to save settings to NVS for %s", key);
  }
}

void settings_fetch_all(){
  for(int i=0; i < N_AXIS; i++)
    fetch_axis_config(i);

  for(int i=0; i < N_STEPPERS; i++)
    fetch_stepper_config(i);

  for(int i=0; i < N_SPINDLES; i++)
    fetch_spindle_config(i);
}

void fetch_axis_config(unsigned int idx){
  if(idx >= N_AXIS) return;

  char axis_config_key[16];
  sprintf(axis_config_key, "axis_%u", idx);

  fetch_config_from_nvs(axis_config_key, &axis_config[idx], sizeof(axis_config_t));
}

void save_axis_config(unsigned int idx){
  if(idx >= N_AXIS) return;

  char axis_config_key[16];
  sprintf(axis_config_key, "axis_%u", idx);

  save_config_to_nvs(axis_config_key, &axis_config[idx], sizeof(axis_config_t));
}

void fetch_stepper_config(unsigned int idx){
  if(idx >= N_STEPPERS) return;

  char stepper_config_key[16];
  sprintf(stepper_config_key, "stepper_%u", idx);

  fetch_config_from_nvs(stepper_config_key, &stepper_config[idx], sizeof(stepper_config_t));
}

void save_stepper_config(unsigned int idx){
  if(idx >= N_STEPPERS) return;

  char stepper_config_key[16];
  sprintf(stepper_config_key, "stepper_%u", idx);

  save_config_to_nvs(stepper_config_key, &stepper_config[idx], sizeof(stepper_config_t));
}

void fetch_spindle_config(unsigned int idx){
  if(idx >= N_SPINDLES) return;

  char spindle_config_key[16];
  sprintf(spindle_config_key, "spindle_%u", idx);

  fetch_config_from_nvs(spindle_config_key, &spindle_config[idx], sizeof(spindle_config_t));
}

void save_spindle_config(unsigned int idx){
  if(idx >= N_SPINDLES) return;

  char spindle_config_key[16];
  sprintf(spindle_config_key, "spindle_%u", idx);

  save_config_to_nvs(spindle_config_key, &spindle_config[idx], sizeof(spindle_config_t));
}

void fetch_galvanometer_config(unsigned int idx){
  if(idx >= N_GALVANOMETERS) return;

  char spindle_config_key[16];
  sprintf(spindle_config_key, "spindle_%u", idx);

  fetch_config_from_nvs(spindle_config_key, &spindle_config[idx], sizeof(spindle_config_t));
}

void save_galvanometer_config(unsigned int idx){
  if(idx >= N_GALVANOMETERS) return;

  char spindle_config_key[16];
  sprintf(spindle_config_key, "spindle_%u", idx);

  save_config_to_nvs(spindle_config_key, &spindle_config[idx], sizeof(spindle_config_t));
}

