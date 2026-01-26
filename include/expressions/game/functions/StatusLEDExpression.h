//
// Created by Ezra Golombek on 01/12/2025.
//

#ifndef PHISITERPETER_ESP32_STATUSLEDEXPRESSION_H
#define PHISITERPETER_ESP32_STATUSLEDEXPRESSION_H
#include "SmartLeds.h"
#include "expressions/BaseExpression.h"


class StatusLEDExpression : public BaseExpression {
    std::unique_ptr<BaseExpression> r;
    std::unique_ptr<BaseExpression> g;
    std::unique_ptr<BaseExpression> b;

public:
    static SmartLed leds;
    std::string expressionName() override;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    StatusLEDExpression(std::unique_ptr<BaseExpression> r, std::unique_ptr<BaseExpression> g, std::unique_ptr<BaseExpression> b);
};


#endif //PHISITERPETER_ESP32_STATUSLEDEXPRESSION_H
