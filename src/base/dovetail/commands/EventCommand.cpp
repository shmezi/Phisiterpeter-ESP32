//
// Created by Ezra Golombek on 11/06/2026.
//

#include "../../../../include/base/dovetail/commands/EventCommand.h"

#include "base/ScheduleLoop.h"

std::string EventCommand::name() {
    return "event";
}

void EventCommand::execute(JsonDocument doc) {
    ScheduleLoop::getInstance()->runEvent(doc["id"], doc["value"]);
}
