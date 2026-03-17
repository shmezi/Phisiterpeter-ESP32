//
// Created by Ezra Golombek on 11/03/2026.
//

#include "../../include/base/DovetailCore.h"

#include <esp_http_server.h>
#include <esp_log.h>
#include <esp_mac.h>
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
        esp_wifi_connect();
        debug::warn("WiFi was disconnected! Attempting to reconnect!");
    } else if (base == IP_EVENT && id == IP_EVENT_STA_GOT_IP) {
        // Reset retry counter on successful connection

        xEventGroupClearBits(s_wifi_event_group, WIFI_FAIL_BIT);
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);

        auto *event = static_cast<ip_event_got_ip_t *>(data);

        ESP_LOGI("WIFI", "Got IP: " IPSTR, IP2STR(&event->ip_info.ip));
    }
}


// Handler for /reset
esp_err_t PostReset(httpd_req_t *req) {
    debug::showColor(debug::RESTART);
    const char *resp_str = "Phisiland Core is now resting!";
    httpd_resp_send(req, resp_str, strlen(resp_str));
    debug::log("Rebooting deveice via remote command!");
    // Logic to reset your DovetailCore or the ESP32
    vTaskDelay(pdMS_TO_TICKS(1000));
    esp_restart();
    return ESP_OK;
}

esp_err_t PostEvent(httpd_req_t *req) {
    char buf[64]; // Buffer for the query string
    char val_str[10] = {0};
    ESP_LOGI("SERVER", "Free Internal: %d, Free PSRAM: %d",
             heap_caps_get_free_size(MALLOC_CAP_8BIT | MALLOC_CAP_INTERNAL),
             heap_caps_get_free_size(MALLOC_CAP_SPIRAM));

    // 1. Get the full query string (everything after the '?')
    if (httpd_req_get_url_query_str(req, buf, sizeof(buf)) == ESP_OK) {
        // 2. Extract specific parameters
        httpd_query_key_value(buf, "val", val_str, sizeof(val_str));
    }

    // 3. Convert extracted string to Integer
    int resultValue = atoi(val_str);

    // 4. Send response back to the client
    const char *resp_str = "Event Started";
    httpd_resp_send(req, resp_str, strlen(resp_str));

    // 5. Trigger your logic using the parsed integer
    // Passing the integer from ?val=
    ScheduleLoop::getInstance()->startEvent(resultValue);

    return ESP_OK;
}

std::string DovetailCore::codebase = "print \"Debug Your Code\"";

httpd_handle_t DovetailCore::startWebServer() {
    httpd_handle_t server = nullptr;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    if (httpd_start(&server, &config) != ESP_OK) {
        debug::runTimeError("Failed to start server");
        return nullptr;
    }

    debug::log("Server started successfully, registering URI handlers...");


    constexpr httpd_uri_t resetURI = {
        .uri = "/reset",
        .method = HTTP_GET,
        .handler = PostReset,
        .user_ctx = nullptr
    };
    constexpr httpd_uri_t eventURI = {
        .uri = "/event",
        .method = HTTP_GET,
        .handler = PostEvent,
        .user_ctx = nullptr
    };

    httpd_register_uri_handler(server, &resetURI);
    httpd_register_uri_handler(server, &eventURI);

    return server;
}

std::string incomingData;

esp_err_t DovetailCore::httpClientHandler(esp_http_client_event_t *evt) {
    switch (evt->event_id) {
        case HTTP_EVENT_ON_CONNECTED:
            // Clear the string for a fresh start
            incomingData.clear();
            break;

        case HTTP_EVENT_ON_DATA:
            if (evt->data_len > 0) {
                // Safely append the incoming chunk to our string
                incomingData.append(static_cast<char *>(evt->data), evt->data_len);
            }
            break;

        case HTTP_EVENT_ON_FINISH: {
            char url_buffer[128];
            // Get the URL that was just requested
            esp_http_client_get_url(evt->client, url_buffer, sizeof(url_buffer));
            if (strstr(url_buffer, "/code")) {
                // WE can push this back if we see this doesnt function..
                debug::log("Code command!");
                codebase = incomingData;
                // Trigger your interpreter here or set a flag
                Interpreter::runInterpreter(codebase);
            }
            break;
        }
        default:
            break;
    }
    return ESP_OK;
}


bool DovetailCore::sendGetRequest(const std::string &url) {
    std::string full_url = "http://192.168.4.1/" + url;

    esp_http_client_config_t config = {
        .url = full_url.c_str(),
        .method = HTTP_METHOD_GET,
        .event_handler = httpClientHandler,
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = esp_http_client_perform(client);
    esp_http_client_cleanup(client);
    if (err != ESP_OK) {
        debug::runTimeError(("HTTP GET request to " + std::string(esp_err_to_name(err)) + "failed :("));
        return false;
    }
    return true;
}

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
        EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
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

    return std::string(mac_cstr);
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

    // Register the handlers
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifiNetworkHandler, NULL, NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifiNetworkHandler, NULL, NULL))
    ;

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    debug::showColor(debug::WIFI_SUCCESS);
}

void DovetailCore::innitDovetail() {
    connectWifi();
    scanAndJoin();
    startWebServer();
}
