//
// Created by Ezra Golombek on 11/03/2026.
//

#include "../../include/base/DovetailCore.h"

#include <esp_http_server.h>
#include <esp_log.h>
#include <esp_wifi.h>
#include <string>

#include "esp_http_client.h"
#include "Utils.h"
#include "base/Interpreter.h"

// Bits for synchronization
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1
static EventGroupHandle_t s_wifi_event_group;

// 1. The Event Handler (Must be registered in your main init)
void DovetailCore::wifiNetworkHandler(void *arg, esp_event_base_t base, int32_t id, void *data) {
    if (base == WIFI_EVENT && id == WIFI_EVENT_STA_DISCONNECTED) {
        xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
    } else if (base == IP_EVENT && id == IP_EVENT_STA_GOT_IP) {
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

std::string DovetailCore::codebase = "";

httpd_handle_t DovetailCore::startWebServer() {
    httpd_handle_t server = nullptr;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    if (httpd_start(&server, &config) == ESP_OK) {
        debug::log("Server started successfully, registering URI handlers...");
        return server;
    }

    debug::error("Failed to start server");
    return nullptr;
}

std::string incoming_code;

esp_err_t DovetailCore::httpClientHandler(esp_http_client_event_t *evt) {
    switch (evt->event_id) {
        case HTTP_EVENT_ON_CONNECTED:
            // Clear the string for a fresh start
            incoming_code.clear();
            break;

        case HTTP_EVENT_ON_DATA:
            if (evt->data_len > 0) {
                // Safely append the incoming chunk to our string
                incoming_code.append(static_cast<char *>(evt->data), evt->data_len);
            }
            break;

        case HTTP_EVENT_ON_FINISH:
            // Now that the data is complete, point codebase to it
            codebase = const_cast<char *>(incoming_code.c_str());
            // Trigger your interpreter here or set a flag
            Interpreter::runInterpreter(codebase);
            break;

        default:
            break;
    }
    return ESP_OK;
}

void DovetailCore::send_get_request(const std::string &url) {
    std::string full_url = "http://" + url;

    esp_http_client_config_t config = {
        .url = full_url.c_str(),
        .method = HTTP_METHOD_GET,
        .event_handler = httpClientHandler,
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = esp_http_client_perform(client);

    if (err != ESP_OK) {
        debug::error(("HTTP GET request to " + std::string(esp_err_to_name(err)) + "failed :("));
    }

    esp_http_client_cleanup(client);
}

void DovetailCore::scanAndJoin() {
    // 1. Scan
    wifi_scan_config_t scan_config = {};
    esp_wifi_scan_start(&scan_config, true);
    vTaskDelay(pdMS_TO_TICKS(3000)); //Delay start to allow for monitor
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
        EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
                                               WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                               pdTRUE, pdFALSE, pdMS_TO_TICKS(10000));

        if (bits & WIFI_CONNECTED_BIT) {
            debug::log("Connected to: " + ssid_str);
            break;
        }

        debug::log("Failed to connect to: " + ssid_str);
        esp_wifi_disconnect();
    }
    free(ap_list);
}

void DovetailCore::connectWifi() {
    // Initialize Event Group
    s_wifi_event_group = xEventGroupCreate();

    // Standard Init (Assuming NVS is already init in app_main)
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    // Register the handler
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifiNetworkHandler, NULL, NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifiNetworkHandler, NULL, NULL))
    ;

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    vTaskDelay(pdMS_TO_TICKS(3000)); //Delay start to allow for monitor
}

void DovetailCore::innitSystem() {
    connectWifi();
    scanAndJoin();
    startWebServer();
}
