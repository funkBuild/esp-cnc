#include "job_api.h"
#include "api_util.h"
#include "../job.h"

#include "esp_log.h"
#include "cJSON.h"

#include <string.h>

void send_job_json(http_req *req){
  cJSON *json = job_to_json();    
  char *json_string = cJSON_PrintUnformatted(json);

  api_send_ok(req, json_string);

  cJSON_Delete(json);
  free(json_string);
}

void job_send_error(http_req *req, job_err_t error){
  switch(error){
    case JOB_ERR_ALREADY_INITIALIZED:
      api_send_error(req, "{\"error\":\"job already initialized\"}");
      break;
    case JOB_ERR_FILE_NOT_FOUND:
      api_send_error(req, "{\"error\":\"file not found\"}");
      break;
    case JOB_ERR_NOT_INITIALIZED:
      api_send_error(req, "{\"error\":\"job not initialized\"}");
      break;
    case JOB_ERR_NOT_RUNNING:
      api_send_error(req, "{\"error\":\"job not running\"}");
      break;
    case JOB_ERR_RUNNING:
      api_send_error(req, "{\"error\":\"job is running\"}");
      break;
    default:
      api_send_error(req, "{\"error\":\"unknown error\"}");
      break;
  }
}

void job_post_handler(http_req *req){
  cJSON *input_json = api_get_body_as_json(req);

  if(input_json == NULL){
    api_send_invalid_json(req);
    return;
  }
  
  cJSON *filename_value = cJSON_GetObjectItemCaseSensitive(input_json, "filename");
  if (cJSON_IsString(filename_value)) {
    job_err_t ret = job_create(filename_value->valuestring);

    if(ret == JOB_OK)
      send_job_json(req);
    else
      job_send_error(req, ret);
  } else {
    api_send_error(req, "{\"error\":\"filename required\"}");
  }

  cJSON_Delete(input_json);
}

void job_get_handler(http_req *req){
  send_job_json(req);
}

void job_delete_handler(http_req *req){
  job_err_t ret = job_destroy();

  if(ret == JOB_OK)
    send_job_json(req);
  else
    job_send_error(req, ret);
}

void job_start_handler(http_req *req){
  job_err_t ret = job_start();

  if(ret == JOB_OK)
    send_job_json(req);
  else
    job_send_error(req, ret);
}

void job_stop_handler(http_req *req){
  job_err_t ret = job_stop();

  if(ret == JOB_OK)
    send_job_json(req);
  else
    job_send_error(req, ret);
}

void job_pause_handler(http_req *req){
  job_err_t ret = job_pause();

  if(ret == JOB_OK)
    send_job_json(req);
  else
    job_send_error(req, ret);
}
