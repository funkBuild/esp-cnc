#include "axis_api.h"
#include "api_util.h"
#include "../stepper.h"
#include "../settings.h"

#include "esp_log.h"
#include "cJSON.h"

#include <string.h>

cJSON* get_stepper_config_json(int idx){
  cJSON *json = cJSON_CreateObject();
  cJSON_AddNumberToObject(json, "index", idx);
  cJSON_AddStringToObject(json, "axis", axis_idx_to_string(stepper_config[idx].axis));
  cJSON_AddBoolToObject(json, "enabled", stepper_config[idx].enabled);
  cJSON_AddNumberToObject(json, "steps_per_mm", stepper_config[idx].steps_per_mm);

  return json;
}

void stepper_config_post_handler(http_req *req){
  char motor_idx_string[16];
  sscanf( req->url, "/config/stepper/%s", motor_idx_string );

  int idx = strtol(motor_idx_string, NULL, 10);

  if(idx < 0 || idx > N_STEPPERS){
    api_send_not_found(req, "{\"error\":\"invalid_stepper_index\"}");
    return;
  }

  cJSON *input_json = api_get_body_as_json(req);
  if(input_json == NULL){
    api_send_invalid_json(req);
    return;
  }

  cJSON *enabled_value = cJSON_GetObjectItemCaseSensitive(input_json, "enabled");
  if (cJSON_IsBool(enabled_value)) {
    stepper_config[idx].enabled = enabled_value->valueint;
  }

  cJSON *steps_per_mm_value = cJSON_GetObjectItemCaseSensitive(input_json, "steps_per_mm");
  if (cJSON_IsNumber(steps_per_mm_value)) {
    stepper_config[idx].steps_per_mm = steps_per_mm_value->valuedouble;
  }

  cJSON *axis_value = cJSON_GetObjectItemCaseSensitive(input_json, "axis");
  if (cJSON_IsString(axis_value)) {
    stepper_config[idx].axis = axis_string_to_idx(axis_value->valuestring);
  }

  save_stepper_config(idx);

  cJSON *json = get_stepper_config_json(idx);    
  char *json_string = cJSON_PrintUnformatted(json);

  api_send_ok(req, json_string);

  cJSON_Delete(json);
  free(json_string);
}

void stepper_all_config_get_handler(http_req *req){
  cJSON *json = cJSON_CreateObject();
  cJSON *steppers = cJSON_AddArrayToObject(json, "steppers");

  for(int i=0; i < N_STEPPERS; i++){
    cJSON_AddItemToArray(steppers, get_stepper_config_json(i));
  }

  char *json_string = cJSON_PrintUnformatted(json);

  api_send_ok(req, json_string);

  cJSON_Delete(json);
  free(json_string);
}

void stepper_config_get_handler(http_req *req){
  char motor_idx_string[16];
  sscanf( req->url, "/config/stepper/%s", motor_idx_string );

  int motor_idx = strtol(motor_idx_string, NULL, 10);

  if(motor_idx < 0 || motor_idx > N_STEPPERS){
    const char* error_string = "{\"error\":\"invalid_stepper_index\"}";

    api_send_not_found(req, error_string);
  } else {
    cJSON *json = get_stepper_config_json(motor_idx);
    char *json_string = cJSON_PrintUnformatted(json);

    api_send_ok(req, json_string);

    cJSON_Delete(json);
    free(json_string);
  }
}
