//
// Created by Ezra Golombek on 11/03/2026.
//

#include "base/dovetail/DovetailCore.h"

#include <esp_http_server.h>
#include <esp_log.h>
#include <esp_mac.h>
#include <esp_wifi.h>
#include <string>

#include "Utils.h"
#include "base/Interpreter.h"
#include "base/dovetail/DovetailClient.h"
#include "base/dovetail/DovetailMessageHandler.h"
#include "base/dovetail/DovetailWifi.h"
#include "base/dovetail/DovetailWS.h"

// Bits for synchronization

SemaphoreHandle_t DovetailCore::dovetailRegisteredSuccessfully = xSemaphoreCreateBinary();
array<uint8_t, 6> DovetailCore::selfMac;
std::string DovetailCore::prettyMac;
bool DovetailCore::shouldUpdateCodeBase = false;
SemaphoreHandle_t DovetailCore::shutdownWS = xSemaphoreCreateBinary();


std::string DovetailCore::codebase = "print \"Debug Your Code\"";

std::vector<wifi_ap_record_t> DovetailCore::scanNetworks() {
    wifi_scan_config_t scan_config = {};
    esp_wifi_scan_start(&scan_config, true);

    uint16_t ap_count = 0;
    esp_wifi_scan_get_ap_num(&ap_count);
    std::vector<wifi_ap_record_t> ap_list(ap_count);
    if (ap_count > 0) {
        esp_wifi_scan_get_ap_records(&ap_count, ap_list.data());
    }
    return ap_list;
}

bool DovetailCore::isDovetailNetwork(const std::string &ssid) {
    return ssid.starts_with("Dovetail-");
}

void DovetailCore::connectToNetwork(const wifi_ap_record_t &network) {
    wifi_config_t wifi_config = {};
    strcpy(reinterpret_cast<char *>(wifi_config.sta.password), "Phisiland"); // Insert known password
    memcpy(wifi_config.sta.ssid, network.ssid, sizeof(wifi_config.sta.ssid));


    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    esp_wifi_connect();
}

bool DovetailCore::validateRegisteration() {
    if (xSemaphoreTake(dovetailRegisteredSuccessfully, pdMS_TO_TICKS(10000)) == pdTRUE) {
        debug::log("Successfully registered!");
        debug::showColor(debug::JOINED_NETWORK);
        xSemaphoreGive(dovetailRegisteredSuccessfully);

        return true;
    }
    debug::runTimeError("Device failed registration, (Most likely Server is lagging). Moving on.");

    return false;
}

bool DovetailCore::validateConnection() {
    const EventBits_t bits = xEventGroupWaitBits(
        DovetailWifi::s_wifi_event_group,
        WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
        pdTRUE,
        pdFALSE,
        pdMS_TO_TICKS(10000));

    if (bits & WIFI_CONNECTED_BIT) {
        debug::log("Connected to network!");

        debug::showColor(debug::JOINED_NETWORK);
        return true;
    }
    return false;
}

void DovetailCore::onFailedNetworkScan() {
    debug::log("Failed to connect to any network. Retrying shortly!");
}

bool DovetailCore::hasDovetailRegistered() {
    const auto isRegistered = xSemaphoreTake(dovetailRegisteredSuccessfully, 0) == pdTRUE;
    if (isRegistered)
        xSemaphoreGive(dovetailRegisteredSuccessfully);
    return isRegistered;
}

void DovetailCore::scanAndConnect() {
    debug::log("Attempting to join networks!");
    debug::showColor(debug::SEARCHING_NETWORK);


    for (const auto &network: scanNetworks()) {
        std::string ssid = utils::bytesToString(network.ssid);

        if (!isDovetailNetwork(ssid)) continue;

        debug::log("Attempting to join network: " + ssid);

        //I switched delay from 2000 to 20!!! PLEASE MAKE SURE IT STILL FUNCTIONS 11/03/26 - 09/06/26 I think it works, great work me :)
        vTaskDelay(pdMS_TO_TICKS(20));

        connectToNetwork(network);

        // Wait for Success or Failure (10 second timeout)
        if (!validateConnection()) {
            esp_wifi_disconnect();
            continue;
        }

        DovetailWS::initWS();
        if (validateRegisteration()) {
            loadAndExecuteCodebase();
            break;
        }

        debug::log("Failed to connect to: " + ssid);

        esp_wifi_disconnect();
    }
}

std::string DovetailCore::getFormattedMacAddress() {
    uint8_t mac[6];
    char mac_cstr[18];

    // Read the base MAC address for the Wi-Fi station interface
    esp_read_mac(mac, ESP_MAC_WIFI_STA);

    // Format into standard notation
    snprintf(mac_cstr, sizeof(mac_cstr), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    return mac_cstr;
}

array<uint8_t, 6> DovetailCore::getMacAddress() {
    array<uint8_t, 6> mac;
    esp_read_mac(mac.data(), ESP_MAC_WIFI_STA);
    return mac;
}

void DovetailCore::loadCodebase() {
}

void DovetailCore::loadAndExecuteCodebase() {
    DovetailClient::sendGetRequest("code?mac=" + prettyMac);
}

void shutdown_handler_task(void *arg) {
    for (;;) {
        xSemaphoreTake(DovetailCore::shutdownWS, portMAX_DELAY);
        DovetailWS::stopWS();
        esp_wifi_disconnect();
    }
}

void DovetailCore::innitDovetail() {
    DovetailWifi::initWifiClient();
    DovetailMessageHandler::registerAllInternalCommands();
    xTaskCreate(shutdown_handler_task, "ws_shutdown", 4096, nullptr, 1, nullptr);

    debug::log("© 2026 Dovetail System by Ezra Golombek, has started.");
    while (true) {
        scanAndConnect();
        if (hasDovetailRegistered()) break;
        onFailedNetworkScan();
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}
