//
// Created by Ezra Golombek on 11/06/2026.
//

#include "../../../../include/base/dovetail/commands/EventCommand.h"

#include "base/ScheduleLoop.h"
#include "logging/Logger.h"

std::string EventCommand::name() {
    return "event";
}

void EventCommand::execute(JsonDocument doc) {
    Logger::log("Executing!");
    ScheduleLoop::getInstance()->runEvent(doc["id"], doc["value"]);
}
