/* (c) 2024 M10tech
 * bare-esp32-homekit-demo
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_wifi.h"

// You must set VERSION=x.y.z of the code to match github version tag x.y.z via e.g. version.txt file

void main_task(void *arg) {
    printf("the beginning\n");
    
    while (true) {
        printf("hi there\n");
        vTaskDelay(200);
    }
}    

void app_main(void) {
    printf("app_main-start\n");

    //The code in this function would be the setup for any app that uses wifi which is set by LCM
    //It is all boilerplate code that is also used in common_example code
    esp_err_t err = nvs_flash_init(); // Initialize NVS
    if (err==ESP_ERR_NVS_NO_FREE_PAGES || err==ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase()); //NVS partition truncated and must be erased
        err = nvs_flash_init(); //Retry nvs_flash_init
    } ESP_ERROR_CHECK( err );

    //block that gets you WIFI with the lowest amount of effort, and based on FLASH
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    esp_netif_inherent_config_t esp_netif_config = ESP_NETIF_INHERENT_DEFAULT_WIFI_STA();
    esp_netif_config.route_prio = 128;
    esp_netif_create_wifi(WIFI_IF_STA, &esp_netif_config);
    esp_wifi_set_default_wifi_sta_handlers();
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_FLASH));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(esp_wifi_connect());
    //end of boilerplate code

    xTaskCreate(main_task,"main",4096,NULL,1,NULL);
    while (true) {
        vTaskDelay(1000); 
    }
    printf("app_main-done\n"); //will never exit here
}
