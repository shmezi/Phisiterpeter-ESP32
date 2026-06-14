//
// Created by Ezra Golombek on 09/06/2026.
//

#include "../../../include/base/dovetail/DovetailWifi.h"

#include <esp_event_base.h>
#include <esp_log.h>
#include <esp_wifi.h>
#include <esp_wifi_types_generic.h>


#include "Utils.h"
#include "base/dovetail/DovetailCore.h"

EventGroupHandle_t DovetailWifi::s_wifi_event_group;
// 1. The Event Handler (Must be registered in your main init)
void DovetailWifi::wifiNetworkHandler(void *arg, esp_event_base_t base, int32_t id, void *data) {
    if (base == WIFI_EVENT && id == WIFI_EVENT_STA_DISCONNECTED) {
        // esp_wifi_connect();
        //TODO WE NEED TO ADD A STATUS FOR THE ENTIRE SYSTEM!
        // debug::warn("WiFi was disconnected! Attempting to reconnect!");
    } else if (base == IP_EVENT && id == IP_EVENT_STA_GOT_IP) {
        // Reset retry counter on successful connection

        xEventGroupClearBits(s_wifi_event_group, WIFI_FAIL_BIT);
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);

        auto *event = static_cast<ip_event_got_ip_t *>(data);

        ESP_LOGI("WIFI", "Got IP: " IPSTR, IP2STR(&event->ip_info.ip));
    }
}

void DovetailWifi::initWifiClient() {
    // Initialize Event Group
    s_wifi_event_group = xEventGroupCreate();
    ESP_LOGI("DEBUG", "Step 1 - before wifi init, heap: %lu", esp_get_free_heap_size());

    // Standard Init (Assuming NVS is already init in app_main)
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_LOGI("DEBUG", "Step 2 - before connect, heap: %lu", esp_get_free_heap_size());

    // Register the handlers
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifiNetworkHandler, NULL, NULL));
    ESP_ERROR_CHECK(
        esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifiNetworkHandler, NULL, NULL));
    ESP_LOGI("DEBUG", "Step 3 - connected, heap: %lu", esp_get_free_heap_size());

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    debug::showColor(debug::WIFI_SUCCESS);
}
