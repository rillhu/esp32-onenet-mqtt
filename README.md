> based on ESP-IDF Release v3.3's official mqtt lib

> Code will be updated both in github and gitee(master):
>
> [gitee](https://gitee.com/rillhu/esp32-onenet-mqtt.git) [github](https://github.com/rillhu/esp32-onenet-mqtt.git)

# Adapt for onenet MQTT(old)

### Pre-cond

- ESP-IDF

  - Based on [ESP-IDF Release v3.3 (LTS) ](https://github.com/espressif/esp-idf/releases/tag/v3.3),Documentation for release v3.3 is available at https://docs.espressif.com/projects/esp-idf/en/v3.3/ 
  - This archive can also be downloaded from Espressif's download server:
    https://dl.espressif.com/dl/esp-idf/releases/esp-idf-v3.3.zip

- Compile tool

  https://dl.espressif.com/dl/esp32_win32_msys2_environment_and_toolchain-20181001.zip

- other changes see code: Add push ds18b20 temperature to onetnet



# ESP-MQTT sample application

(See the README.md file in the upper level 'examples' directory for more information about examples.)

This example connects to the broker URI selected using `make menuconfig` (using mqtt tcp transport) and as a demonstration subscribes/unsubscribes and send a message on certain topic.
Note: If the URI equals `FROM_STDIN` then the broker address is read from stdin upon application startup (used for testing)

It uses ESP-MQTT library which implements mqtt client to connect to mqtt broker.

## How to use example

### Hardware Required

This example can be executed on any ESP32 board, the only required interface is WiFi and connection to internet.

### Configure the project

```
make menuconfig
```

* Set serial port under Serial Flasher Options.

* Set ssid and password for the board to connect to AP.

### Build and Flash

Build the project and flash it to the board, then run monitor tool to view serial output:

```
make -j4 flash monitor
```

(To exit the serial monitor, type ``Ctrl-]``.)

See the Getting Started Guide for full steps to configure and use ESP-IDF to build projects.

## Example Output

```
I (3714) event: sta ip: 192.168.0.139, mask: 255.255.255.0, gw: 192.168.0.2
I (3714) system_api: Base MAC address is not set, read default base MAC address from BLK0 of EFUSE
I (3964) MQTT_CLIENT: Sending MQTT CONNECT message, type: 1, id: 0000
I (4164) MQTT_EXAMPLE: MQTT_EVENT_CONNECTED
I (4174) MQTT_EXAMPLE: sent publish successful, msg_id=41464
I (4174) MQTT_EXAMPLE: sent subscribe successful, msg_id=17886
I (4174) MQTT_EXAMPLE: sent subscribe successful, msg_id=42970
I (4184) MQTT_EXAMPLE: sent unsubscribe successful, msg_id=50241
I (4314) MQTT_EXAMPLE: MQTT_EVENT_PUBLISHED, msg_id=41464
I (4484) MQTT_EXAMPLE: MQTT_EVENT_SUBSCRIBED, msg_id=17886
I (4484) MQTT_EXAMPLE: sent publish successful, msg_id=0
I (4684) MQTT_EXAMPLE: MQTT_EVENT_SUBSCRIBED, msg_id=42970
I (4684) MQTT_EXAMPLE: sent publish successful, msg_id=0
I (4884) MQTT_CLIENT: deliver_publish, message_length_read=19, message_length=19
I (4884) MQTT_EXAMPLE: MQTT_EVENT_DATA
TOPIC=/topic/qos0
DATA=data
I (5194) MQTT_CLIENT: deliver_publish, message_length_read=19, message_length=19
I (5194) MQTT_EXAMPLE: MQTT_EVENT_DATA
TOPIC=/topic/qos0
DATA=data
```
