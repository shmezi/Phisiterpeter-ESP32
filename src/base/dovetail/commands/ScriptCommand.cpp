//
// Created by Ezra Golombek on 10/06/2026.
//

#include "base/dovetail/commands/ScriptCommand.h"

#include <esp_system.h>

#include "Utils.h"

std::string ScriptCommand::name() {
    return "script";
}

void ScriptCommand::execute(JsonDocument doc) {
    debug::log("DovetailEditor has requested a reboot! Rebooting ESP!");
    esp_restart();
}
