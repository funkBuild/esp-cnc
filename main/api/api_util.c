#include "../global.h"

#include "esphttpd.h"
#include "cJSON.h"

#include <string.h>

Axis axis_string_to_idx(char* axis_string){
  if(strlen(axis_string) == 0 || strlen(axis_string) > 1)
    return -1;

  // TODO: Support upper case. Maybe convert all urls to lowercase in httpd?
  switch(axis_string[0]){
    case 'x':
      return X_AXIS;
    case 'y':
      return Y_AXIS;
    case 'z':
      return Z_AXIS;
    default:
      return INVALID_AXIS;
  }
}

char* axis_idx_to_string(Axis axis){
  switch(axis){
    case X_AXIS:
      return "x";
    case Y_AXIS:
      return "y";
    case Z_AXIS:
      return "z";
    default:
      return "-";
  }
}

void api_send_internal_error(http_req *req, const char* body){
  http_res res = {
    .status_code = 500,
    .status_text = "Internal Server Error",
    .content_type = "application/json",
    .body = body,
    .body_len = strlen(body)
  };

  webserver_send_response(req, &res);
}

void api_send_error(http_req *req, const char* error_string){
  http_res res = {
    .status_code = 400,
    .status_text = "Bad Request",
    .content_type = "application/json",
    .body = error_string,
    .body_len = strlen(error_string)
  };

  webserver_send_response(req, &res);
}

void api_send_invalid_json(http_req *req){
  const char* error_string = "{\"error\":\"invalid_json\"}";

  api_send_error(req, error_string);
}

void api_send_not_found(http_req *req, const char* error_string){
  http_res res = {
    .status_code = 404,
    .status_text = "Not Found",
    .content_type = "application/json",
    .body = error_string,
    .body_len = strlen(error_string)
  };

  webserver_send_response(req, &res);
}

void api_send_ok(http_req *req, const char* body){
  http_res res = {
    .status_code = 200,
    .status_text = "OK",
    .content_type = "application/json",
    .body = body,
    .body_len = strlen(body)
  };

  webserver_send_response(req, &res);
}

cJSON* api_get_body_as_json(http_req *req){
  char body[128] = {0};
  webserver_recv_body(req, body, sizeof(body));

  return cJSON_Parse(body);
}
