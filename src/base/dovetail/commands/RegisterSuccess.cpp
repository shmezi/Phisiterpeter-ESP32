//
// Created by Ezra Golombek on 10/06/2026.
//

#include "base/dovetail/commands/RegisterSuccess.h"


#include "base/dovetail/DovetailCore.h"

std::string RegisterSuccess::name() {
    return "register_success";
}

void RegisterSuccess::execute(JsonDocument doc) {
    xSemaphoreGive(DovetailCore::dovetailRegisteredSuccessfully);
}
