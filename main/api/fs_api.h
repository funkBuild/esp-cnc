#pragma once
#include "esphttpd.h"

void fs_get_handler(http_req *req);
void fs_post_handler(http_req *req);
void fs_options_handler(http_req *req);
void fs_delete_handler(http_req *req);
