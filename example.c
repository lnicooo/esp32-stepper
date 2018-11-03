#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "driver/stepper.h"

esp_err_t event_handler(void *ctx, system_event_t *event)
{
    return ESP_OK;
}

void app_main(void)
{
    nvs_flash_init();
    
    struct stepper_pins stepper0;
    
    stepper0.pin1 = 27;
    stepper0.pin2 = 26;
    stepper0.pin3 = 25;
    stepper0.pin4 = 33;    
   
    stepper_init(&stepper0);

    while (true) {
        
        full_steps(&stepper0, 100, CW);
        vTaskDelay(1000 / portTICK_PERIOD_MS);   
        full_steps(&stepper0, 100, CCW); 
        vTaskDelay(1000 / portTICK_PERIOD_MS);  

    }
}
c
