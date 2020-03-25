#include "string.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "rom/ets_sys.h"
#include "esp_log.h"

#define TAG "LED"


bool led_task_run = true;
bool led_toggle = false;
unsigned int led_blink_freq = 5000;

void led_task(void *pv)
{
    int led_gpio = GPIO_NUM_2;
    gpio_config_t conf = {
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
        .pin_bit_mask = 1<<led_gpio //GPIO 2 connect LED, high level is LED on.
    };

    if(gpio_config(&conf)==ESP_OK){
    	ESP_LOGI(TAG,"Setup for %s connected to GPIO%d", "LED", led_gpio);
    } else {
    	ESP_LOGE(TAG,"Error in %s connected to GPIO%d\n", "LED",led_gpio);
    }

    gpio_set_direction(led_gpio, GPIO_MODE_OUTPUT);
    gpio_set_level(led_gpio, 0);

    char led_blink_times = 0;
    char blink_times_max = 2*8;//on and off will let cnt +2
    while (1){
        if (led_task_run){
        	if (led_toggle == false){
                gpio_set_level(led_gpio, 1);
                led_toggle = true;
                vTaskDelay(led_blink_freq / portTICK_RATE_MS);
        	}else{
                gpio_set_level(led_gpio, 0);
                led_toggle = false;
                //led_task_run = false;
                vTaskDelay(led_blink_freq / portTICK_RATE_MS);
        	}

            if(led_blink_freq==200){
                led_blink_times++;
                led_blink_freq = led_blink_times>blink_times_max?5000:200;
                led_blink_times = led_blink_times>blink_times_max?0:led_blink_times;
            }
        }
        vTaskDelay(100 / portTICK_RATE_MS);
    }
}

