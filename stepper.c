#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "driver/stepper.h"

const uint8_t steps_port[8] = {0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};

void stepper_init(struct stepper_pins *stepper_ptr)
{
    gpio_set_direction(stepper_ptr->pin1,GPIO_MODE_OUTPUT);
    gpio_set_direction(stepper_ptr->pin2,GPIO_MODE_OUTPUT);
    gpio_set_direction(stepper_ptr->pin3,GPIO_MODE_OUTPUT);
    gpio_set_direction(stepper_ptr->pin4,GPIO_MODE_OUTPUT);

}

void step(struct stepper_pins *stepper_ptr, int step)
{
    gpio_set_level(stepper_ptr->pin1,step&1);
    gpio_set_level(stepper_ptr->pin2,(step&2)>>1);
    gpio_set_level(stepper_ptr->pin3,(step&4)>>2);
    gpio_set_level(stepper_ptr->pin4,(step&8)>>3);
}

void full_steps(struct stepper_pins *stepper_ptr,int steps, bool dir)
{       
    int n;
    int i = 0;

    if(dir){
        i=0;
		for(n=0;n<steps;n++){
		    if(i>8)
		        i=0;
		    step(stepper_ptr, steps_port[i]);
		    vTaskDelay(5 / portTICK_PERIOD_MS);    
		    i++;
		}
    }

    else{
        i=7;
		for(n=0;n<steps;n++){
		    if(i<0)
		        i=7;
		    step(stepper_ptr, steps_port[i]);
		    vTaskDelay(5 / portTICK_PERIOD_MS);    
		    i--;
		}
    }
}

