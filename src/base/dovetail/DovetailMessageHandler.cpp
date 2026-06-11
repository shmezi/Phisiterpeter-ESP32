//
// Created by Ezra Golombek on 10/06/2026.
//

#include "base/dovetail/DovetailMessageHandler.h"


#include <map>

#include "Utils.h"
#include "base/dovetail/commands/Command.h"
#include "base/dovetail/commands/RegisterFailureCommand.h"
#include "base/dovetail/commands/RegisterSuccessCommand.h"
#include "base/dovetail/commands/ScriptCommand.h"
#include "logging/Logger.h"
std::map<std::string, std::unique_ptr<Command> > DovetailMessageHandler::commands;


void DovetailMessageHandler::onIncomingMessage(JsonDocument &doc) {
    const char *cmdName = doc["command"];
    if (!cmdName) {
        Logger::warn("No command field in JSON!");
        return;
    }
    const auto command = commands.find(cmdName);

    if (command == commands.end()) {
        Logger::warn("Command not found!");
        return;
    }
    command->second->execute(doc);
}

void DovetailMessageHandler::registerCommand(std::unique_ptr<Command> command) {
    const std::string name = command->name();
    commands[name] = std::move(command);
}

void DovetailMessageHandler::registerAllInternalCommands() {
    registerCommand(std::make_unique<RegisterFailureCommand>());
    registerCommand(std::make_unique<RegisterSuccessCommand>());
    registerCommand(std::make_unique<ScriptCommand>());

}
