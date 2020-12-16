#include "axis_api.h"
#include "api_util.h"
#include "../spindle.h"
#include "../settings.h"

#include "esp_log.h"
#include "cJSON.h"

#include <string.h>

cJSON* get_spindle_config_json(int idx){
  cJSON *json = cJSON_CreateObject();
  cJSON_AddNumberToObject(json, "index", idx);
  cJSON_AddBoolToObject(json, "enabled", spindle_config[idx].enabled);
  cJSON_AddStringToObject(json, "output_type", spindle_config[idx].output_type == PWM ? "pwm" : "analog");
  cJSON_AddBoolToObject(json, "dynamic_power", spindle_config[idx].dynamic_power);
  cJSON_AddNumberToObject(json, "max_rpm", spindle_config[idx].max_speed);

  if(spindle_config[idx].output_type == PWM)
    cJSON_AddNumberToObject(json, "frequency", spindle_config[idx].frequency);
  else
    cJSON_AddNumberToObject(json, "analog_channel_idx", spindle_config[idx].analog_channel_idx);

  return json;
}


void spindle_config_post_handler(http_req *req){
  char spindle_idx_string[16];
  sscanf( req->url, "/config/spindle/%s", spindle_idx_string );

  int idx = strtol(spindle_idx_string, NULL, 10);

  if(idx < 0 || idx > N_SPINDLES){
    api_send_not_found(req, "{\"error\":\"invalid_spindle_index\"}");
    return;
  }

  cJSON *input_json = api_get_body_as_json(req);
  if(input_json == NULL){
    api_send_invalid_json(req);
    return;
  }

  cJSON *enabled_value = cJSON_GetObjectItemCaseSensitive(input_json, "enabled");
  if (cJSON_IsBool(enabled_value)) {
    spindle_config[idx].enabled = enabled_value->valueint;
  }

  cJSON *output_type_value = cJSON_GetObjectItemCaseSensitive(input_json, "output_type");
  if (cJSON_IsString(output_type_value)) {
    if(strcmp(output_type_value->valuestring, "pwm") == 0)
      spindle_config[idx].output_type = PWM;
    else if(strcmp(output_type_value->valuestring, "analog") == 0)
      spindle_config[idx].output_type = Analog;
    // TODO: else throw an error
  }

  cJSON *dynamic_power_value = cJSON_GetObjectItemCaseSensitive(input_json, "dynamic_power");
  if (cJSON_IsBool(dynamic_power_value)) {
    spindle_config[idx].dynamic_power = enabled_value->valueint;
  }

  cJSON *max_rpm_value = cJSON_GetObjectItemCaseSensitive(input_json, "max_rpm");
  if (cJSON_IsNumber(max_rpm_value)) {
    spindle_config[idx].max_speed = max_rpm_value->valueint;
  }

  if(spindle_config[idx].output_type == PWM){
    cJSON *frequency_value = cJSON_GetObjectItemCaseSensitive(input_json, "frequency");
    if (cJSON_IsNumber(frequency_value)) {
      spindle_config[idx].frequency = frequency_value->valueint;
    }
  } else if(spindle_config[idx].output_type == Analog){
    cJSON *analog_channel_idx_value = cJSON_GetObjectItemCaseSensitive(input_json, "analog_channel_idx");
    if (cJSON_IsNumber(analog_channel_idx_value) && analog_channel_idx_value->valueint >= 0 && analog_channel_idx_value->valueint <= 1) {
      spindle_config[idx].analog_channel_idx = analog_channel_idx_value->valueint;
    }
  }

  cJSON_Delete(input_json);
  save_spindle_config(idx);

  cJSON *json = get_spindle_config_json(idx);    
  char *json_string = cJSON_PrintUnformatted(json);

  api_send_ok(req, json_string);

  cJSON_Delete(json);
  free(json_string);
}

void spindle_all_config_get_handler(http_req *req){
  cJSON *json = cJSON_CreateObject();
  cJSON *steppers = cJSON_AddArrayToObject(json, "spindles");

  for(int i=0; i < N_SPINDLES; i++){
    cJSON_AddItemToArray(steppers, get_spindle_config_json(i));
  }

  char *json_string = cJSON_PrintUnformatted(json);

  api_send_ok(req, json_string);

  cJSON_Delete(json);
  free(json_string);
}

void spindle_config_get_handler(http_req *req){
  char spindle_idx_string[16];
  sscanf( req->url, "/config/spindle/%s", spindle_idx_string );

  int spindle_idx = strtol(spindle_idx_string, NULL, 10);

  if(spindle_idx < 0 || spindle_idx > N_SPINDLES){
    const char* error_string = "{\"error\":\"invalid_spindle_index\"}";

    api_send_not_found(req, error_string);
  } else {
    cJSON *json = get_spindle_config_json(spindle_idx);    
    char *json_string = cJSON_PrintUnformatted(json);

    api_send_ok(req, json_string);

    cJSON_Delete(json);
    free(json_string);
  }
}
