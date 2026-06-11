//
// Created by Ezra Golombek on 10/06/2026.
//

#ifndef PHISITERPETER_ESP32_DOVETAILMESSAGEHANDLER_H
#define PHISITERPETER_ESP32_DOVETAILMESSAGEHANDLER_H
#include <map>
#include <memory>
#include <ArduinoJson.h>
#include <functional>

#include "commands/Command.h"


class DovetailMessageHandler {
    static std::map<std::string, std::unique_ptr<Command> > commands;

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


#endif //PHISITERPETER_ESP32_DOVETAILMESSAGEHANDLER_H
