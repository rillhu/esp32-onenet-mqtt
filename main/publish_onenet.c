#include "string.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "rom/ets_sys.h"
#include "esp_log.h"

#include "mqtt_client.h"
#include "cJSON.h"

#include "led_task.h"
#include "ds18b20.h"
#include "led_task.h"


#define TAG "ONENET"

void publish_onenet_task(void *pv)
{
    while (1){
            led_blink_freq = 200;

#if 1
            esp_mqtt_client_handle_t client = (esp_mqtt_client_handle_t) pv;
            cJSON *root = cJSON_CreateObject();
			if(dsb20_temp!=0.0){
                cJSON_AddNumberToObject(root,"Temperature",dsb20_temp);
            }
//            cJSON_AddNumberToObject(root,"Illumination",   bh_illumination);

            char *out = cJSON_Print(root);
            ESP_LOGI(TAG, "%s", out);
            char *data = (char *)malloc(strlen(out)+3);
            data[0] = 3; //data type
            data[1] = 0x00;
            data[2] = strlen(out);
            memcpy(&data[3],out,strlen(out));
			esp_mqtt_client_publish(client, "$dp", data, strlen(out)+3, 0, 0);
            free(data);
            cJSON_Delete(root);
            free(out);
#endif
#if 1
            //GPS raw data: 3412.7253,N,10850.1386
            //Covert baidu map format: 34. 12/60+0.7253/60, 108.50/60+0.1386/60
            const char *str = "{\"datastreams\":[{\"id\":\"location\",\"datapoints\":[{\"value\":{\"lon\":108.83564333,\"lat\":34.21208833}}]}]}";
            ESP_LOGI(TAG, "%s", str);
            char data_array[128];
            data_array[0] = 1; //data type
            data_array[1] = 0x00;
            data_array[2] = strlen(str);
            memcpy(&data_array[3],str,strlen(str));
			esp_mqtt_client_publish(client, "$dp", data_array, strlen(str)+3, 0, 0);
#endif
        vTaskDelay(60000 / portTICK_RATE_MS);
    }
}

