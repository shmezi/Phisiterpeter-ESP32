//
// Created by Ezra Golombek on 10/06/2026.
//

#include "base/dovetail/commands/RegisterSuccessCommand.h"


#include "base/dovetail/DovetailCore.h"

std::string RegisterSuccessCommand::name() {
    return "register_success";
}

void RegisterSuccessCommand::execute(JsonDocument doc) {
    xSemaphoreGive(DovetailCore::dovetailRegisteredSuccessfully);
}
