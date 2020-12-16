#pragma once

#include "stdbool.h"
#include <stdio.h>
#include "cJSON.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define JOB_BUFFER_SIZE 64

typedef enum {
  JOB_STATE_EMPTY,
  JOB_STATE_STOPPED,
  JOB_STATE_PAUSED,
  JOB_STATE_RUNNING,
  JOB_STATE_ERROR
} job_state;

typedef enum {
  JOB_OK = 0,
  JOB_ERR_FILE_NOT_FOUND,
  JOB_ERR_ALREADY_INITIALIZED,
  JOB_ERR_NOT_INITIALIZED,
  JOB_ERR_NOT_RUNNING,
  JOB_ERR_RUNNING,
  JOB_ERR_GCODE_PARSE_FAIL
} job_err_t;

typedef struct job_context_t {
  job_state state;
  char* filename;
  FILE* f;
  TaskHandle_t job_thread_handle;
} job_context_t;

cJSON* job_to_json();
job_err_t job_create(char *file_path);
job_err_t job_destroy();
job_err_t job_stop();
job_err_t job_start();
job_err_t job_pause();
job_err_t job_resume();
