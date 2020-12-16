#include "fs_api.h"
#include "api_util.h"
#include "esp_vfs_fat.h"
#include <sys/unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include "esp_log.h"
#include "cJSON.h"

#include <string.h>

static const char *TAG = "SD_CARD";
static const char* base_path = "/sdcard/";

//TODO: Check if SD card is actually mounted

void get_folder(http_req *req, char *path){
  cJSON *json = cJSON_CreateObject();
  DIR *dp;
  struct dirent *ep;     
  dp = opendir(path);

  if(dp != NULL) {
    cJSON *result = cJSON_AddArrayToObject(json, "files");

    while((ep = readdir(dp)) != NULL){
      char filepath[255];

      strcpy(filepath, path);
      strcat(filepath, "/");
      strcat(filepath, ep->d_name);

      struct stat st;
      stat(filepath, &st);

      cJSON *entry = cJSON_CreateObject();
      cJSON_AddStringToObject(entry, "name", ep->d_name);

      if(ep->d_type == 1){
        cJSON_AddStringToObject(entry, "type", "f");
        cJSON_AddNumberToObject(entry, "size", st.st_size);
      } else {
        cJSON_AddStringToObject(entry, "type", "d");
      }

      
      cJSON_AddItemToArray(result, entry);
    }

    closedir(dp);

    FATFS *fs;
    DWORD fre_clust, fre_sect, tot_sect;

    /* Get volume information and free clusters of drive 0 */
    int res = f_getfree("0:", &fre_clust, &fs);
    /* Get total sectors and free sectors */
    tot_sect = (fs->n_fatent - 2) * fs->csize;
    fre_sect = fre_clust * fs->csize;

    cJSON_AddNumberToObject(json, "free_space", fre_sect / 2);
    cJSON_AddNumberToObject(json, "total_space", tot_sect / 2);

    char *json_string = cJSON_PrintUnformatted(json);
    api_send_ok(req, json_string);

    cJSON_Delete(json);
    free(json_string);

  } else {
    api_send_internal_error(req, "\"error\":\"sd_card_read_error\"}");
  }
}

void get_file(http_req *req, char *path){
  webserver_send_file_response(req, path, "text/plain");
}

void get_full_path(char *dst, http_req *req){
  char directory_string[128] = {0};
  sscanf( req->url, "/fs/%s", directory_string );
  sprintf(dst, "%s%s", base_path, directory_string);
}

void fs_get_handler(http_req *req){
  char path[128] = {0};
  get_full_path(path, req);

  struct stat st;

  if (stat(path, &st) == -1) {
    api_send_not_found(req, "{\"error\":\"not found\"}");
    return;
  }

  if(S_ISREG(st.st_mode))
    get_file(req, path);
  else if(S_ISDIR(st.st_mode))
    get_folder(req, path);
  else
    api_send_not_found(req, "{\"error\":\"not found\"}");
}

void fs_post_handler(http_req *req){
  char path[128] = {0};
  get_full_path(path, req);

  webserver_pipe_body_to_file(req, path);

  api_send_ok(req, "{\"success\":true}");
}

void fs_options_handler(http_req *req){
  webserver_send_status(req, 200, "OK");
  webserver_send_header(req, "Access-Control-Allow-Origin", "*");
  webserver_send_header(req, "Access-Control-Allow-Methods", "GET, POST, PUT, DELETE");
  webserver_send_header(req, "Access-Control-Allow-Headers",  "Content-Type");
  webserver_send_header(req, "Access-Control-Max-Age", "86400");
  webserver_send_header(req, "Content-Length", "0");
}

void fs_delete_handler(http_req *req){
  char path[128] = {0};
  get_full_path(path, req);

  int ret = remove(path);

  if(ret == 0)
    api_send_ok(req, "{\"success\":true}");
  else
    api_send_not_found(req, "{\"success\":false}");
}
