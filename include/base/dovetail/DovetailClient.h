//
// Created by Ezra Golombek on 09/06/2026.
//

#ifndef PHISITERPETER_ESP32_DOVETAILCLIENT_H
#define PHISITERPETER_ESP32_DOVETAILCLIENT_H
#include <esp_http_client.h>
#include <string>

class DovetailClient {
    static std::string incomingData;

    static esp_err_t httpClientHandler(esp_http_client_event_t *evt);

public:
    static bool sendGetRequest(const std::string &url);
};


#endif //PHISITERPETER_ESP32_DOVETAILCLIENT_H
