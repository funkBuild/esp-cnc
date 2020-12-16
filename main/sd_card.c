#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "driver/sdmmc_host.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"
#include "cJSON.h"
#include <sys/stat.h>



static const char *TAG = "SD_CARD";

void sd_card_benchmark(int block_size){
  const int count = (1024*1024) / block_size;
  char *buf = malloc(block_size);
  //esp_fill_random(buf, block_size);

  unsigned long start_time = esp_timer_get_time();
  
  FILE* f = fopen("/sdcard/hello.txt", "wb");

  if (f == NULL)
  {
      printf("Error opening file!\n");
      return;
  }

  for(int i = 0; i < count; i++){
    int ret = fwrite(buf, block_size, 1, f);
    if(ret <= 0)
      printf("Write failed\n");
  }
  
  fclose(f);
  free(buf);

  double delta_time = (esp_timer_get_time() - start_time) / (1000.0 * 1000.0);
  double result = 1024.0 / delta_time;
  printf("bs=%d, count=%d, kB/s=%f, t=%f\n", block_size, count, result, delta_time);

  remove("/sdcard/hello.txt");
}

void sd_card_task(){
  ESP_LOGI(TAG, "Initializing SD card");

  sdmmc_host_t host = SDMMC_HOST_DEFAULT();
  host.slot = 1;
  //host.command_timeout_ms = 5000;
  host.max_freq_khz = SDMMC_FREQ_52M;

  // This initializes the slot without card detect (CD) and write protect (WP) signals.
  // Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.
  sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
  slot_config.width = 1;


  gpio_set_pull_mode(15, GPIO_PULLUP_ONLY);   // CMD, needed in 4- and 1- line modes
  gpio_set_pull_mode(2, GPIO_PULLUP_ONLY);    // D0, needed in 4- and 1-line modes
  gpio_set_pull_mode(4, GPIO_PULLUP_ONLY);    // D1, needed in 4-line mode only
  gpio_set_pull_mode(12, GPIO_PULLUP_ONLY);   // D2, needed in 4-line mode only
  gpio_set_pull_mode(13, GPIO_PULLUP_ONLY);   // D3, needed in 4- and 1-line modes

  esp_vfs_fat_sdmmc_mount_config_t mount_config = {
    .format_if_mount_failed = false,
    .max_files = 5,
    .allocation_unit_size = 16 * 1024
  };

  sdmmc_card_t* card;

  while(true){
    esp_err_t ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK) {
      if (ret == ESP_FAIL) {
        ESP_LOGE(TAG, "Failed to mount filesystem. "
            "If you want the card to be formatted, set format_if_mount_failed = true.");
      } else {
        ESP_LOGE(TAG, "Failed to initialize the card (%s). "
            "Make sure SD card lines have pull-up resistors in place.", esp_err_to_name(ret));
      }

      vTaskDelay(3000/portTICK_PERIOD_MS);
    } else {
      break;
    }
  }

  // Card has been initialized, print its properties
  sdmmc_card_print_info(stdout, card);
  size_t width = sdmmc_host_get_slot_width(1);
  printf("Slot width = %d\n", width);
/*
  sd_card_get_directory("/sdcard");

    // Use POSIX and C standard library functions to work with files.
    // First create a file.
    ESP_LOGI(TAG, "Opening file");
    FILE* f = fopen("/sdcard/hello.txt", "w");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for writing");
        return;
    }
    fprintf(f, "Hello %s!\n", card->cid.name);
    fclose(f);
    ESP_LOGI(TAG, "File written");

    // Check if destination file exists before renaming
    struct stat st;
    if (stat("/sdcard/foo.txt", &st) == 0) {
        // Delete it if it exists
        unlink("/sdcard/foo.txt");
    }

    // Rename original file
    ESP_LOGI(TAG, "Renaming file");
    if (rename("/sdcard/hello.txt", "/sdcard/foo.txt") != 0) {
        ESP_LOGE(TAG, "Rename failed");
        return;
    }

    // Open renamed file for reading
    ESP_LOGI(TAG, "Reading file");
    f = fopen("/sdcard/foo.txt", "r");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for reading");
        return;
    }
    char line[64];
    fgets(line, sizeof(line), f);
    fclose(f);
    // strip newline
    char* pos = strchr(line, '\n');
    if (pos) {
        *pos = '\0';
    }
    ESP_LOGI(TAG, "Read from file: '%s'", line);

*/
/*
  esp_vfs_fat_sdmmc_unmount();
  ESP_LOGI(TAG, "Card unmounted");
  vTaskDelay(3000/portTICK_PERIOD_MS);
*/
  sd_card_benchmark(4096);
/*
  sd_card_benchmark(512);
  sd_card_benchmark(1024);
  sd_card_benchmark(2048);
  sd_card_benchmark(4096);
  sd_card_benchmark(8192);
  sd_card_benchmark(16384);
  sd_card_benchmark(32708);
  sd_card_benchmark(65536);
*/
  while(1){
    vTaskDelay(1000000/portTICK_PERIOD_MS);
  }

  vTaskDelete( NULL );
}

void sd_card_init()
{
  xTaskCreate(
    sd_card_task,
    "sd_card_task",
    4096,
    NULL,
    9,
    NULL
  );
}
