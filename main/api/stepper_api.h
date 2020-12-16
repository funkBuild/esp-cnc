#pragma once

#include "esphttpd.h"

void stepper_config_post_handler(http_req *req);
void stepper_all_config_get_handler(http_req *req);
void stepper_config_get_handler(http_req *req);
