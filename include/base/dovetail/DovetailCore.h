//
// Created by Ezra Golombek on 11/03/2026.
//

#ifndef PHISITERPETER_ESP32_DOVETAILCORE_H
#define PHISITERPETER_ESP32_DOVETAILCORE_H
#include <esp_event_base.h>
#include <esp_http_client.h>
#include <esp_http_server.h>
#include <string>

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

class DovetailCore {
public:
    static std::string codebase;


    static void scanAndJoin();

    static std::string getMacAddress();


    static void innitDovetail();
};


#endif //PHISITERPETER_ESP32_DOVETAILCORE_H
