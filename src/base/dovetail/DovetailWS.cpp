//
// Created by Ezra Golombek on 09/06/2026.
//

#include "base/dovetail/DovetailWS.h"

#include <esp_log.h>

#include "esp_websocket_client.h"
#include "Utils.h"
#include <ArduinoJson.h>  // works fine via lib_deps

esp_websocket_client_handle_t DovetailWS::client = nullptr;


void DovetailWS::websocket_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id,
                                         void *event_data) {
    auto *data = static_cast<esp_websocket_event_data_t *>(event_data);

    switch (event_id) {
        case WEBSOCKET_EVENT_CONNECTED:
            // JsonDocument doc;
            debug::log("Successfully connected to WebSocket Server!");
            // Send a test message immediately upon connection
            esp_websocket_client_send_text(client, "Hello from ESP32-S3!", 20, portMAX_DELAY);
            break;

        case WEBSOCKET_EVENT_DISCONNECTED:
            debug::warn("Disconnected from server.");
            break;

        case WEBSOCKET_EVENT_DATA: {
            if (data->op_code == 0x09 || data->op_code == 0x0A) {
                debug::log("Still playing ping pong :)");
                break; // Drop it, ESP-IDF automatically sends the Pong back!
            }
            //


            std::string message(data->data_ptr, data->data_len);
            JsonDocument doc;
            deserializeJson(doc, message);
            // Log incoming messages safely without spilling over memory limits
            debug::log("Received message: " + doc["name"]);
            break;
        }

        case WEBSOCKET_EVENT_ERROR:
            debug::runTimeError("An error occurred inside the WS loop.");
            break;
    }
}

void DovetailWS::initWS() {
    esp_websocket_client_config_t config{
        .uri = "ws://192.168.4.1/ws"
    };
    client = esp_websocket_client_init(&config);
    esp_websocket_register_events(client, WEBSOCKET_EVENT_ANY, websocket_event_handler, nullptr);
    esp_websocket_client_start(client);
}
