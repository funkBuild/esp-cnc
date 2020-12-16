#pragma once

#include "esphttpd.h"

void spindle_config_post_handler(http_req *req);
void spindle_all_config_get_handler(http_req *req);
void spindle_config_get_handler(http_req *req);
