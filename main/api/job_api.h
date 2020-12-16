#pragma once

#include "esphttpd.h"

void job_post_handler(http_req *req);
void job_get_handler(http_req *req);
void job_delete_handler(http_req *req);
void job_start_handler(http_req *req);
void job_stop_handler(http_req *req);
void job_pause_handler(http_req *req);
