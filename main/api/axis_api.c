#include "axis_api.h"
#include "api_util.h"

#include "../global.h"
#include "../settings.h"

#include "esp_log.h"
#include "cJSON.h"

#include <string.h>

cJSON* get_axis_config_json(Axis axis){
  cJSON *json = cJSON_CreateObject();
  cJSON_AddStringToObject(json, "axis", axis_config[axis].identifier);
  cJSON_AddBoolToObject(json, "enabled", axis_config[axis].enabled);
  cJSON_AddNumberToObject(json, "acceleration_limit", axis_config[axis].acceleration_limit);
  cJSON_AddNumberToObject(json, "velocity_limit", axis_config[axis].velocity_limit);

  return json;
}

void axis_config_post_handler(http_req *req){
  char axis_string[16];
  sscanf( req->url, "/config/axis/%s", axis_string );

  Axis axis = axis_string_to_idx(axis_string);

  if(axis == INVALID_AXIS){
    const char* error_string = "{\"error\":\"invalid_axis\"}";
    api_send_not_found(req, error_string);
    return;
  }

  cJSON *input_json = api_get_body_as_json(req);
  if(input_json == NULL){
    api_send_invalid_json(req);
    return;
  }
  
  cJSON *enabled_value = cJSON_GetObjectItemCaseSensitive(input_json, "enabled");
  if (cJSON_IsBool(enabled_value)) {
    axis_config[axis].enabled = enabled_value->valueint;
  }

  cJSON *acceleration_value = cJSON_GetObjectItemCaseSensitive(input_json, "acceleration_limit");
  if (cJSON_IsNumber(acceleration_value)) {
    axis_config[axis].acceleration_limit = acceleration_value->valuedouble;
  }

  cJSON *velocity_value = cJSON_GetObjectItemCaseSensitive(input_json, "velocity_limit");
  if (cJSON_IsNumber(velocity_value)) {
    axis_config[axis].velocity_limit = velocity_value->valuedouble;
  }

  cJSON_Delete(input_json);
  save_axis_config(axis);

  cJSON *json = get_axis_config_json(axis);    
  char *json_string = cJSON_PrintUnformatted(json);

  api_send_ok(req, json_string);

  cJSON_Delete(json);
  free(json_string);
}

void all_axis_config_get_handler(http_req *req){
  cJSON *json = cJSON_CreateObject();
  cJSON *axes = cJSON_AddArrayToObject(json, "axes");

  for(int i=0; i < N_AXIS; i++){
    cJSON_AddItemToArray(axes, get_axis_config_json(i));
  }

  char *json_string = cJSON_PrintUnformatted(json);

  api_send_ok(req, json_string);

  cJSON_Delete(json);
  free(json_string);
}

void axis_config_get_handler(http_req *req){
  char axis_string[16];
  sscanf( req->url, "/config/axis/%s", axis_string );

  Axis axis = axis_string_to_idx(axis_string);

  if(axis == INVALID_AXIS){
    const char* error_string = "{\"error\":\"invalid_axis\"}";

    api_send_not_found(req, error_string);
  } else {
    cJSON *json = get_axis_config_json(axis);    
    char *json_string = cJSON_PrintUnformatted(json);

    api_send_ok(req, json_string);

    cJSON_Delete(json);
    free(json_string);
  }
}
