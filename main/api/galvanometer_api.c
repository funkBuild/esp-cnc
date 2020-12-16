#include "galvanometer_api.h"
#include "api_util.h"
#include "../galvanometer.h"
#include "../settings.h"

#include "esp_log.h"
#include "cJSON.h"

#include <string.h>

cJSON* get_galvanometer_config_json(int idx){
  cJSON *json = cJSON_CreateObject();
  cJSON_AddNumberToObject(json, "index", idx);
  cJSON_AddStringToObject(json, "axis", axis_idx_to_string(galvanometer_config[idx].axis));
  cJSON_AddBoolToObject(json, "enabled", galvanometer_config[idx].enabled);
  cJSON_AddNumberToObject(json, "width", galvanometer_config[idx].width);

  return json;
}

void galvanometer_config_post_handler(http_req *req){
  char idx_string[16];
  sscanf( req->url, "/config/galvanometer/%s", idx_string );

  int idx = strtol(idx_string, NULL, 10);

  if(idx < 0 || idx > N_GALVANOMETERS){
    api_send_not_found(req, "{\"error\":\"invalid_galvanometer_index\"}");
    return;
  }

  cJSON *input_json = api_get_body_as_json(req);
  if(input_json == NULL){
    api_send_invalid_json(req);
    return;
  }

  cJSON *enabled_value = cJSON_GetObjectItemCaseSensitive(input_json, "enabled");
  if (cJSON_IsBool(enabled_value)) {
    galvanometer_config[idx].enabled = enabled_value->valueint;
  }

  cJSON *width_value = cJSON_GetObjectItemCaseSensitive(input_json, "width");
  if (cJSON_IsNumber(width_value)) {
    galvanometer_config[idx].width = width_value->valuedouble;
  }

  cJSON *axis_value = cJSON_GetObjectItemCaseSensitive(input_json, "axis");
  if (cJSON_IsString(axis_value)) {
    galvanometer_config[idx].axis = axis_string_to_idx(axis_value->valuestring);
  }

  cJSON_Delete(input_json);
  save_galvanometer_config(idx);

  cJSON *json = get_galvanometer_config_json(idx);    
  char *json_string = cJSON_PrintUnformatted(json);

  api_send_ok(req, json_string);

  cJSON_Delete(json);
  free(json_string);
}

void galvanometer_all_config_get_handler(http_req *req){
  cJSON *json = cJSON_CreateObject();
  cJSON *galvanometers = cJSON_AddArrayToObject(json, "galvanometers");

  for(int i=0; i < N_GALVANOMETERS; i++){
    cJSON_AddItemToArray(galvanometers, get_galvanometer_config_json(i));
  }

  char *json_string = cJSON_PrintUnformatted(json);

  api_send_ok(req, json_string);

  cJSON_Delete(json);
  free(json_string);
}

void galvanometer_config_get_handler(http_req *req){
  char idx_string[16];
  sscanf( req->url, "/config/galvanometer/%s", idx_string );

  int motor_idx = strtol(idx_string, NULL, 10);

  if(motor_idx < 0 || motor_idx > N_GALVANOMETERS){
    const char* error_string = "{\"error\":\"invalid_galvanometer_index\"}";

    api_send_not_found(req, error_string);
  } else {
    cJSON *json = get_galvanometer_config_json(motor_idx);
    char *json_string = cJSON_PrintUnformatted(json);

    api_send_ok(req, json_string);

    cJSON_Delete(json);
    free(json_string);
  }
}
