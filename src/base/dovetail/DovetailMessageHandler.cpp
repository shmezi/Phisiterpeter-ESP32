//
// Created by Ezra Golombek on 10/06/2026.
//

#include "base/dovetail/DovetailMessageHandler.h"


#include <functional>
#include <map>

#include "esp_websocket_client.h"
#include "Utils.h"
#include "base/dovetail/DovetailCore.h"
#include "base/dovetail/DovetailWS.h"
#include "base/dovetail/commands/Command.h"
#include "base/dovetail/commands/EventCommand.h"
#include "base/dovetail/commands/RegisterFailureCommand.h"
#include "base/dovetail/commands/RegisterSuccessCommand.h"
#include "base/dovetail/commands/ScriptCommand.h"
#include "logging/Logger.h"

static std::map<std::string, std::unique_ptr<Command> > &getCommands() {
    static std::map<std::string, std::unique_ptr<Command> > commands;
    return commands;
}


void DovetailMessageHandler::onIncomingMessage(JsonDocument &doc) {
    const char *cmdName = doc["command"];
    if (!cmdName) {
        Logger::warn("No command field in JSON!");
        return;
    }
    const auto command = getCommands().find(cmdName);

    if (command == getCommands().end()) {
        Logger::warn("Command not found!");
        return;
    }
    command->second->execute(doc);
}

void DovetailMessageHandler::registerCommand(std::unique_ptr<Command> command) {
    const std::string name = command->name();
    getCommands()[name] = std::move(command);
}


void DovetailMessageHandler::requestRegistration() {
    sendCommand("register", [](JsonDocument &doc) {
        doc["mac"] = DovetailCore::getFormattedMacAddress();
    });
}

void DovetailMessageHandler::sendResult(std::string id, std::string value) {
    sendCommand("result", [id,value](JsonDocument &doc) {
        doc["id"] = id;
        doc["value"] = value;
    });
}


void DovetailMessageHandler::changeScreen(std::string screenId) {
    sendCommand("screen", [screenId](JsonDocument &doc) {
        doc["name"] = screenId;
    });
}


void DovetailMessageHandler::endActivity() {
    sendCommand("endActivity", [](JsonDocument &doc) {
    });
}

void DovetailMessageHandler::sendLog(std::string message) {
    sendCommand("log", [message](JsonDocument &doc) {
        doc["mac"] = DovetailCore::getFormattedMacAddress();
        doc["message"] = message;
    });
}

void DovetailMessageHandler::registerAllInternalCommands() {
    registerCommand(std::make_unique<RegisterFailureCommand>());
    registerCommand(std::make_unique<RegisterSuccessCommand>());
    registerCommand(std::make_unique<ScriptCommand>());
    registerCommand(std::make_unique<EventCommand>());
}
