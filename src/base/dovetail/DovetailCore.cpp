//
// Created by Ezra Golombek on 11/03/2026.
//

#include "base/dovetail/DovetailCore.h"

#include <esp_http_server.h>
#include <esp_log.h>
#include <esp_mac.h>
#include <esp_wifi.h>
#include <string>

#include "esp_http_client.h"
#include "Utils.h"
#include "base/Interpreter.h"
#include "base/dovetail/DovetailWifi.h"

// Bits for synchronization


std::string DovetailCore::codebase = "print \"Debug Your Code\"";


void DovetailCore::scanAndJoin() {
    debug::log("Attempting to join networks!");
    debug::showColor(debug::SEARCHING_NETWORK);
    bool connected = false;
    // 1. Scan
    wifi_scan_config_t scan_config = {};
    esp_wifi_scan_start(&scan_config, true);
    // 2. Retrieve results
    uint16_t ap_count = 0;
    esp_wifi_scan_get_ap_num(&ap_count);
    auto *ap_list = static_cast<wifi_ap_record_t *>(malloc(sizeof(wifi_ap_record_t) * ap_count));
    esp_wifi_scan_get_ap_records(&ap_count, ap_list);

    // 3. Iterate through filtered SSIDs
    for (int i = 0; i < ap_count; i++) {
        std::string ssid_str = reinterpret_cast<char *>(ap_list[i].ssid);

        if (!ssid_str.starts_with("Dovetail-")) continue;

        debug::log("Attempting to join network: " + ssid_str);
        //I switched delay from 2000 to 20!!! PLEASE MAKE SURE IT STILL FUNCTIONS 11/03/26
        vTaskDelay(pdMS_TO_TICKS(20));


        wifi_config_t wifi_config = {};
        strcpy(reinterpret_cast<char *>(wifi_config.sta.password), "Phisiland"); // Insert known password
        memcpy(wifi_config.sta.ssid, ap_list[i].ssid, sizeof(wifi_config.sta.ssid));

        ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
        esp_wifi_connect();

        // 4. Wait for Success or Failure (10 second timeout)
        EventBits_t bits = xEventGroupWaitBits(DovetailWifi::s_wifi_event_group,
                                               WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                               pdTRUE, pdFALSE, pdMS_TO_TICKS(10000));

        if (bits & WIFI_CONNECTED_BIT) {
            debug::log("Connected to: " + ssid_str);
            connected = true;
            debug::showColor(debug::JOINED_NETWORK);
            break;
        }

        debug::log("Failed to connect to: " + ssid_str);
        esp_wifi_disconnect();
    }
    free(ap_list);
    if (connected) return;
    debug::log("Failed to connect to any network. Retrying shortly!");
    vTaskDelay(pdMS_TO_TICKS(3000));
    scanAndJoin();
}

std::string DovetailCore::getMacAddress() {
    uint8_t mac[6];
    char mac_cstr[18];

    // Read the base MAC address for the Wi-Fi station interface
    esp_read_mac(mac, ESP_MAC_WIFI_STA);

    // Format into standard notation
    snprintf(mac_cstr, sizeof(mac_cstr), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    return mac_cstr;
}


void DovetailCore::innitDovetail() {
    DovetailWifi::connectWifi();
    scanAndJoin();
}
