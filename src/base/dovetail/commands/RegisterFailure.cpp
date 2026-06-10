//
// Created by Ezra Golombek on 10/06/2026.
//

#include "base/dovetail/commands/RegisterFailure.h"

#include "base/dovetail/DovetailCore.h"

std::string RegisterFailure::name() {
    return "register_failure";
}

void RegisterFailure::execute(JsonDocument doc) {
    xSemaphoreGive(DovetailCore::shutdownWS);
}
