#include "esphttpd.h"

#include "motion.h"
#include "gcode.h"

#include "api/axis_api.h"
#include "api/stepper_api.h"
#include "api/spindle_api.h"
#include "api/galvanometer_api.h"
#include "api/ws_api.h"
#include "api/fs_api.h"
#include "api/job_api.h"

#include <string.h>




const static char http_index_hml[] = "<!DOCTYPE html>"
      "<html>\n"
      "<head>\n"
      "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
      "  <style type=\"text/css\">\n"
      "    html, body, iframe { margin: 0; padding: 0; height: 100%; }\n"
      "    iframe { display: block; width: 100%; border: none; }\n"
      "  </style>\n"
      "<title>HELLO ESP32</title>\n"
      "</head>\n"
      "<body>\n"
      "<h1>Hello World, from ESP32!</h1>\n"
      "</body>\n"
      "</html>\n";


/*
void web_request_file_handler(struct netconn *conn, http_req *req){
  webserver_send_file_response(conn, "/spiffs/index.html", "text/html");
}
*/



void web_request_handler(http_req *req){
  printf("root handler\n");
  http_res res = {
    .status_code = 200,
    .status_text = "OK",
    .content_type = "text/html",
    .body = http_index_hml,
    .body_len = strlen(http_index_hml)
  };

  webserver_send_response(req, &res);
}


void upload_request_handler(http_req *req){
  char *filename = strrchr(req->url, '/') + 1;
  char path[128];
  snprintf(path, sizeof(path), "/sdcard/%s", filename);

  webserver_pipe_body_to_file(req, path);

  http_res res = {
    .status_code = 200,
    .status_text = "OK",
    .content_type = "text/html",
    .body = http_index_hml,
    .body_len = strlen(http_index_hml)
  };

  webserver_send_response(req->sock, &res);
}


void ws_handler(ws_ctx *ctx, ws_event *event){
  switch(event->event_type){
    case WS_CONNECT:
      webserver_accept_ws(ctx);
      break;

    case WS_MESSAGE:
      printf("payload = '%s'\n", event->payload);
      //webserver_send_ws_message(ctx, "ok", 2);
      break;

    default: 
      return;
  }

}


void web_create_routes(){
  http_route route;

  /*
  *   Axis API
  */

  route.method = POST;
  route.url = "/config/axis/*";
  route.callback = axis_config_post_handler;
  webserver_add_route(route);

  route.method = GET;
  route.url = "/config/axis/*";
  route.callback = axis_config_get_handler;
  webserver_add_route(route);

  route.method = GET;
  route.url = "/config/axis";
  route.callback = all_axis_config_get_handler;
  webserver_add_route(route);

  /*
  *   Motor API
  */

  route.method = POST;
  route.url = "/config/stepper/*";
  route.callback = stepper_config_post_handler;
  webserver_add_route(route);

  route.method = GET;
  route.url = "/config/stepper/*";
  route.callback = stepper_config_get_handler;
  webserver_add_route(route);

  route.method = GET;
  route.url = "/config/stepper";
  route.callback = stepper_all_config_get_handler;
  webserver_add_route(route);

  /*
  *   Spindle API
  */

  route.method = POST;
  route.url = "/config/spindle/*";
  route.callback = spindle_config_post_handler;
  webserver_add_route(route);

  route.method = GET;
  route.url = "/config/spindle/*";
  route.callback = spindle_config_get_handler;
  webserver_add_route(route);

  route.method = GET;
  route.url = "/config/spindle";
  route.callback = spindle_all_config_get_handler;
  webserver_add_route(route);

  /*
  *   Galvanometer API
  */

  route.method = POST;
  route.url = "/config/galvanometer/*";
  route.callback = galvanometer_config_post_handler;
  webserver_add_route(route);

  route.method = GET;
  route.url = "/config/galvanometer/*";
  route.callback = galvanometer_config_get_handler;
  webserver_add_route(route);

  route.method = GET;
  route.url = "/config/galvanometer";
  route.callback = galvanometer_all_config_get_handler;
  webserver_add_route(route);

  /*
  *   FS API
  */

  route.method = POST;
  route.url = "/fs/*";
  route.callback = fs_post_handler;
  webserver_add_route(route);

  route.method = GET;
  route.url = "/fs/*";
  route.callback = fs_get_handler;
  webserver_add_route(route);

  route.method = OPTIONS;
  route.url = "/fs/*";
  route.callback = fs_options_handler;
  webserver_add_route(route);

  route.method = DELETE;
  route.url = "/fs/*";
  route.callback = fs_delete_handler;
  webserver_add_route(route);
  
  /*
  *   Job API
  */

  route.method = POST;
  route.url = "/job";
  route.callback = job_post_handler;
  webserver_add_route(route);

  route.method = GET;
  route.url = "/job";
  route.callback = job_get_handler;
  webserver_add_route(route);

  route.method = DELETE;
  route.url = "/job";
  route.callback = job_delete_handler;
  webserver_add_route(route);

  route.method = POST;
  route.url = "/job/start";
  route.callback = job_start_handler;
  webserver_add_route(route);

  route.method = POST;
  route.url = "/job/stop";
  route.callback = job_stop_handler;
  webserver_add_route(route);

  route.method = POST;
  route.url = "/job/pause";
  route.callback = job_pause_handler;
  webserver_add_route(route);

  /*
  *   WS API
  */

  ws_route ws_route = {
    .url = "/ws",
    .callback = ws_api_handler
  };

  webserver_add_ws_route(ws_route);
}


void web_init()
{
  web_create_routes();
  webserver_start(80);
}
