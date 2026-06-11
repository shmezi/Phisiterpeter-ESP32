//
// Created by Ezra Golombek on 09/06/2026.
//

#include "base/dovetail/DovetailWS.h"

#include <esp_log.h>

#include "esp_websocket_client.h"
#include "Utils.h"
#include <ArduinoJson.h>  // works fine via lib_deps
#include <esp_wifi.h>

#include "base/dovetail/DovetailCore.h"
#include "base/dovetail/DovetailMessageHandler.h"
#include "base/dovetail/DovetailWifi.h"
#include "logging/Logger.h"

esp_websocket_client_handle_t DovetailWS::client = nullptr;

bool DovetailWS::isPingPongMessage(const esp_websocket_event_data_t *data) {
    return data->op_code == 0x09 || data->op_code == 0x0A;
}

void DovetailWS::requestRegistration() {
    JsonDocument doc;
    doc["command"] = "register";
    doc["mac"] = DovetailCore::getFormattedMacAddress();
    char buffer[256];
    const size_t len = serializeJson(doc, buffer, sizeof(buffer));

    esp_websocket_client_send_text(client, buffer, len, portMAX_DELAY);
}

void DovetailWS::websocket_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id,
                                         void *event_data) {
    auto *data = static_cast<esp_websocket_event_data_t *>(event_data);

    switch (event_id) {
        case WEBSOCKET_EVENT_CONNECTED: {
            // JsonDocument doc;
            Logger::log("Successfully connected to WebSocket Server!");
            requestRegistration();
            break;
        }

        case WEBSOCKET_EVENT_DISCONNECTED:
            Logger::warn("Disconnected from server.");
            break;

        case WEBSOCKET_EVENT_DATA: {
            if (isPingPongMessage(data)) break;

            std::string unParsedMessage(data->data_ptr, data->data_len);

            JsonDocument doc;
            deserializeJson(doc, unParsedMessage);
            DovetailMessageHandler::onIncomingMessage(doc);

            break;
        }

        case WEBSOCKET_EVENT_ERROR:
            Logger::error("An error occurred inside the WS loop.");
            break;
    }
}

void DovetailWS::stopWS() {
    if (client != nullptr) {
        esp_websocket_client_stop(client);
        esp_websocket_client_destroy(client);
        client = nullptr;
    }
}

void DovetailWS::initWS() {
    stopWS();

    esp_websocket_client_config_t config{
        .uri = "ws://192.168.4.1/ws"
    };
    client = esp_websocket_client_init(&config);
    esp_websocket_register_events(client, WEBSOCKET_EVENT_ANY, websocket_event_handler, nullptr);
    esp_websocket_client_start(client);
}
