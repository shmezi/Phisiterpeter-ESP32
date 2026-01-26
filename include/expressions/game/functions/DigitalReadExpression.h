//
// Created by Ezra Golombek on 02/12/2025.
//

#ifndef PHISITERPETER_ESP32_DIGITALREAD_H
#define PHISITERPETER_ESP32_DIGITALREAD_H
#include <algorithm>

#include "expressions/BaseExpression.h"
#include "expressions/value/NumberExpression.h"


class DigitalReadExpression : public BaseExpression {
    std::unique_ptr<BaseExpression> pin;


public:
    bool hasRun = false;
    std::string expressionName() override;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    explicit DigitalReadExpression(std::unique_ptr<BaseExpression> pin) : pin(std::move(pin)) {
    };
};


#endif //PHISITERPETER_ESP32_DIGITALREAD_H
