//
// Created by Ezra Golombek on 10/06/2026.
//

#ifndef PHISITERPETER_ESP32_DOVETAILMESSAGEHANDLER_H
#define PHISITERPETER_ESP32_DOVETAILMESSAGEHANDLER_H
#include <map>
#include <memory>
#include <ArduinoJson.h>
#include <functional>

#include "DovetailWS.h"
#include "esp_websocket_client.h"
#include "commands/Command.h"


class DovetailMessageHandler {
public:
    static void onIncomingMessage(JsonDocument &doc);

    static void registerCommand(std::unique_ptr<Command> command);

    static void registerAllInternalCommands();

    template<typename F>
    static void sendCommand(std::string command, F changes);

    static void requestRegistration();

    static void sendResult(std::string id, std::string value);

    static void changeScreen(std::string screenId);

    static void endActivity();

    static void sendLog(std::string message);
};

template<typename F>
void DovetailMessageHandler::sendCommand(std::string command, F changes) {
    JsonDocument doc;

    doc["command"] = command;
    changes(doc);
    char buffer[256];
    const size_t len = serializeJson(doc, buffer, sizeof(buffer));

    esp_websocket_client_send_text(DovetailWS::client, buffer, len, portMAX_DELAY);
}
#endif //PHISITERPETER_ESP32_DOVETAILMESSAGEHANDLER_H
