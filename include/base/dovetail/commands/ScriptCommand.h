//
// Created by Ezra Golombek on 10/06/2026.
//

#ifndef PHISITERPETER_ESP32_SCRIPTCOMMAND_H
#define PHISITERPETER_ESP32_SCRIPTCOMMAND_H
#include "Command.h"


class ScriptCommand : public Command{
public:
    std::string name() override;

    void execute(JsonDocument doc) override;
};


#endif //PHISITERPETER_ESP32_SCRIPTCOMMAND_H
