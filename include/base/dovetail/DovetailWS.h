//
// Created by Ezra Golombek on 09/06/2026.
//

#ifndef PHISITERPETER_ESP32_DOVETAILWS_H
#define PHISITERPETER_ESP32_DOVETAILWS_H
#include "esp_websocket_client.h"

#include <string>


class DovetailWS {
    static bool isPingPongMessage(const esp_websocket_event_data_t *data);


    static void websocket_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);

public:
    static esp_websocket_client_handle_t client;

    static void initWS();

    static void stopWS();
};


#endif //PHISITERPETER_ESP32_DOVETAILWS_H
