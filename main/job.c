#include "job.h"
#include "gcode.h"

#include <string.h>
#include "esp_log.h"

static const char *TAG = "JOB";

/*
  TODO
    created_at, started_at
    add mutex around job struct
*/

job_context_t current_job = {
  .state = JOB_STATE_EMPTY
};

static void job_task( void * pvParameters ){
  char *buf = malloc(JOB_BUFFER_SIZE);
  unsigned int offset = 0, n;
  gcode_err_t err;

  GcodeStreamContext ctx = {
    .current_command = NULL,
    .current_statement = NULL,
    .reached_comment = false,
    .line_number = 0,
    .char_number = 0
  };

  while((n = fread(buf, 1, JOB_BUFFER_SIZE, current_job.f)) != 0){
    err = gcode_process_buffer(&ctx, buf, n);

    if(err != GCODE_OK){
      printf("Gcode parsing error at line %u, character %u\n", ctx.line_number, ctx.char_number);
      // TODO: Report error via websocket
      current_job.state = JOB_STATE_ERROR;
      vTaskSuspend(NULL);
    }
  }

  free(buf);
  current_job.job_thread_handle = NULL;
  current_job.state = JOB_STATE_STOPPED;

  printf("Job complete\n");
  vTaskDelete(NULL);
}

cJSON* job_to_json(){
  cJSON *json = cJSON_CreateObject();

  char *state_string = "empty";

  switch(current_job.state){
    case JOB_STATE_EMPTY:
      break;
    case JOB_STATE_STOPPED:
      state_string = "stopped";
      break;
    case JOB_STATE_PAUSED:
      state_string = "paused";
      break;
    case JOB_STATE_RUNNING:
      state_string = "running";
      break;
    case JOB_STATE_ERROR:
      state_string = "error";
      break;
  }

  cJSON_AddStringToObject(json, "state", state_string);

  if(current_job.state != JOB_STATE_EMPTY){
    cJSON_AddStringToObject(json, "filename", current_job.filename);
  }

  return json;
}

job_err_t job_create(char *file_path){
  if(current_job.state != JOB_STATE_EMPTY){
    ESP_LOGE(TAG, "Job already initialized");
    return JOB_ERR_ALREADY_INITIALIZED;
  }

  char path[64];
  snprintf(path, sizeof(path), "/sdcard/%s", file_path);
  FILE* f = fopen(path, "r");

  if (f == NULL) {
    ESP_LOGE(TAG, "File not found %s", file_path);
    return JOB_ERR_FILE_NOT_FOUND;
  }

  current_job.state = JOB_STATE_STOPPED;
  current_job.filename = strdup(file_path);
  current_job.f = f;

  return JOB_OK;
}

job_err_t job_destroy(){
  if(current_job.state == JOB_STATE_EMPTY){
    return JOB_ERR_NOT_INITIALIZED;
  }

  job_stop();

  fclose(current_job.f);

  current_job.state = JOB_STATE_EMPTY;
  current_job.filename = NULL;
  current_job.f = NULL;

  return JOB_OK;
}

job_err_t job_start(){
  if(current_job.state == JOB_STATE_EMPTY){
    return JOB_ERR_NOT_INITIALIZED;
  }

  if(current_job.state == JOB_STATE_RUNNING){
    return JOB_ERR_RUNNING;
  }

  if(current_job.state == JOB_STATE_STOPPED)
    xTaskCreate(job_task, "job_task", 4096, NULL, tskIDLE_PRIORITY, &current_job.job_thread_handle);
  else
    vTaskResume(current_job.job_thread_handle);

  current_job.state = JOB_STATE_RUNNING;

  return JOB_OK;
}


job_err_t job_stop(){
  if(current_job.state == JOB_STATE_EMPTY){
    return JOB_ERR_NOT_INITIALIZED;
  }

  if(current_job.state == JOB_STATE_STOPPED){
    return JOB_ERR_NOT_RUNNING;
  }

  vTaskDelete(current_job.job_thread_handle);
  current_job.job_thread_handle = NULL;
  current_job.state = JOB_STATE_STOPPED;
  rewind(current_job.f);

  return 0;
}

job_err_t job_pause(){
  if(current_job.state == JOB_STATE_EMPTY){
    return JOB_ERR_NOT_INITIALIZED;
  }

  if(current_job.state != JOB_STATE_RUNNING){
    return JOB_ERR_NOT_RUNNING;
  }

  vTaskSuspend(current_job.job_thread_handle);
  current_job.state = JOB_STATE_PAUSED;

  return JOB_OK;
}
