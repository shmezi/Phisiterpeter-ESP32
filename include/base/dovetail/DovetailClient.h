//
// Created by Ezra Golombek on 09/06/2026.
//

#ifndef PHISITERPETER_ESP32_DOVETAILCLIENT_H
#define PHISITERPETER_ESP32_DOVETAILCLIENT_H
#include <esp_http_client.h>
#include <bits/basic_string.h>


class DovetailClient {
    static esp_err_t httpClientHandler(esp_http_client_event_t *evt);

    static bool sendGetRequest(const std::string &url);
};


#endif //PHISITERPETER_ESP32_DOVETAILCLIENT_H
