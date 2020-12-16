#pragma once

#include "../global.h"
#include "cJSON.h"

Axis axis_string_to_idx(char* axis_string);
char* axis_idx_to_string(Axis axis);
void api_send_internal_error(http_req *req, const char* body);
void api_send_error(http_req *req, const char* error_string);
void api_send_invalid_json(http_req *req);
void api_send_not_found(http_req *req, const char* error_string);
void api_send_ok(http_req *req, const char* body);
cJSON* api_get_body_as_json(http_req *req);
