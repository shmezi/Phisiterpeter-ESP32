//
// Created by Ezra Golombek on 11/03/2026.
//

#ifndef PHISITERPETER_ESP32_DOVETAILCORE_H
#define PHISITERPETER_ESP32_DOVETAILCORE_H
#include <esp_event_base.h>
#include <esp_http_client.h>
#include <esp_http_server.h>
#include <string>


class DovetailCore {
    static void wifiNetworkHandler(void *arg, esp_event_base_t base, int32_t id, void *data);

    static esp_err_t httpClientHandler(esp_http_client_event_t *evt);

public:
    static std::string codebase;
    static void send_get_request(const std::string &url);

    static httpd_handle_t startWebServer();

    static void scanAndJoin();

    static void connectWifi();

    static void innitSystem();
};


#endif //PHISITERPETER_ESP32_DOVETAILCORE_H
