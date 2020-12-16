#pragma once

#include "esphttpd.h"

void axis_config_post_handler(http_req *req);
void all_axis_config_get_handler(http_req *req);
void axis_config_get_handler(http_req *req);
