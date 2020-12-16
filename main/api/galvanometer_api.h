#pragma once

#include "esphttpd.h"

void galvanometer_config_post_handler(http_req *req);
void galvanometer_all_config_get_handler(http_req *req);
void galvanometer_config_get_handler(http_req *req);
