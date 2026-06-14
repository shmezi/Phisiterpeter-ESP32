//
// Created by Ezra Golombek on 09/06/2026.
//

#ifndef PHISITERPETER_ESP32_DOVETAILWIFI_H
#define PHISITERPETER_ESP32_DOVETAILWIFI_H
#include <esp_event_base.h>
#include "freertos/FreeRTOS.h"
#include <freertos/event_groups.h>


class DovetailWifi {
    static void wifiNetworkHandler(void *arg, esp_event_base_t base, int32_t id, void *data);

public:
    static void initWifiClient();

    static EventGroupHandle_t s_wifi_event_group;
};


#endif //PHISITERPETER_ESP32_DOVETAILWIFI_H
