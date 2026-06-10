//
// Created by Ezra Golombek on 10/06/2026.
//

#include "base/dovetail/commands/RegisterFailureCommand.h"

#include "base/dovetail/DovetailCore.h"

std::string RegisterFailureCommand::name() {
    return "register_failure";
}

void RegisterFailureCommand::execute(JsonDocument doc) {
    xSemaphoreGive(DovetailCore::shutdownWS);
}
