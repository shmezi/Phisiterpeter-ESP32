//
// Created by Ezra Golombek on 26/01/2026.
//

#ifndef PHISITERPETER_ESP32_EXPRESSIONINFO_H
#define PHISITERPETER_ESP32_EXPRESSIONINFO_H
#include <string>
#include <vector>
#include "ExpressionArgument.h"

struct ExpressionInfo {
    int indexStart;
    std::string startToken;

    std::vector<ExpressionArgument> argumentNames;
    std::string endToken = " ";
};
#endif //PHISITERPETER_ESP32_EXPRESSIONINFO_H
