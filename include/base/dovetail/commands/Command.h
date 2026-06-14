//
// Created by Ezra Golombek on 10/06/2026.
//

#ifndef PHISITERPETER_ESP32_COMMAND_H
#define PHISITERPETER_ESP32_COMMAND_H

#include <ArduinoJson.h>

class Command {
public:
    virtual ~Command() = default;

    virtual std::string name() = 0;

    virtual void execute(JsonDocument doc) = 0;
};


#endif //PHISITERPETER_ESP32_COMMAND_H
