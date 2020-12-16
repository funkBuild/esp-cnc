#include "esphttpd.h"
#include "../global.h"
#include "../planner.h"

#include <string.h>
#include <stdio.h>

#define WS_POSITION_MSG  1
#define WS_JOB_LINE_NUM_MSG  2

void ws_api_send_position(){
  const int msg_size = 1 + N_AXIS*sizeof(float);
  char msg_buffer[msg_size];

  msg_buffer[0] = WS_POSITION_MSG;
  memcpy(msg_buffer + 1, axis_state.position, N_AXIS*sizeof(float));
  
  webserver_broadcast_ws_message(msg_buffer, msg_size, WS_OP_BIN);
}

void ws_api_send_job_line_number(unsigned int line_number){
  const int msg_size = 1 + sizeof(unsigned int);
  char msg_buffer[msg_size];

  msg_buffer[0] = WS_JOB_LINE_NUM_MSG;
  memcpy(msg_buffer + 1, &line_number, sizeof(unsigned int));
  
  webserver_broadcast_ws_message(msg_buffer, msg_size, WS_OP_BIN);
}

void ws_api_jog(ws_event *event){
  float distance[N_AXIS] = {0};

  memcpy(distance, event->payload+1, event->len);

  add_motion_block(distance, 1, 0);
}

void ws_api_handler(ws_ctx *ctx, ws_event *event){
  switch(event->event_type){
    case WS_CONNECT:
      printf("WS Connected\n");
      webserver_accept_ws(ctx);
      break;

    case WS_MESSAGE:
      //printf("ws payload = '%s'\n", event->payload);
      //webserver_send_ws_message(ctx, "ok", 2);
      ws_api_jog(event);
      break;

    default: 
      return;
  }
}


