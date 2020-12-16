#pragma once

#include "esphttpd.h"

void ws_api_handler(ws_ctx *ctx, ws_event *event);
void ws_api_send_position();
void ws_api_send_job_line_number(unsigned int line_number);
