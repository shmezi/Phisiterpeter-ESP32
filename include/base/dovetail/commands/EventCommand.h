//
// Created by Ezra Golombek on 11/06/2026.
//

#ifndef PHISITERPETER_ESP32_EVENTCOMMAND_H
#define PHISITERPETER_ESP32_EVENTCOMMAND_H
#include "Command.h"


class EventCommand : public Command{
public:
    std::string name() override;

    void execute(JsonDocument doc) override;
};


#endif //PHISITERPETER_ESP32_EVENTCOMMAND_H
