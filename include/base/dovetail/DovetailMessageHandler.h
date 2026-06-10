//
// Created by Ezra Golombek on 10/06/2026.
//

#ifndef PHISITERPETER_ESP32_DOVETAILMESSAGEHANDLER_H
#define PHISITERPETER_ESP32_DOVETAILMESSAGEHANDLER_H
#include <map>
#include <memory>
#include <ArduinoJson.h>
#include "commands/Command.h"


class DovetailMessageHandler {
    static std::map<std::string,  std::unique_ptr<Command>> commands;

public:
    static void onIncomingMessage(JsonDocument &doc);

    static void registerCommand( std::unique_ptr<Command> command);

    static void registerAllInternalCommands();
};


#endif //PHISITERPETER_ESP32_DOVETAILMESSAGEHANDLER_H
