//
// Created by Ezra Golombek on 02/12/2025.
//

#ifndef PHISITERPETER_ESP32_DIGITALREAD_H
#define PHISITERPETER_ESP32_DIGITALREAD_H
#include <algorithm>

#include "expressions/Expression.h"
#include "expressions/value/NumberExpression.h"


class DigitalReadExpression : public Expression {
    std::unique_ptr<Expression> pin;


public:
    bool hasRun = false;
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    explicit DigitalReadExpression(std::unique_ptr<Expression> pin) : pin(std::move(pin)) {
    };
};


#endif //PHISITERPETER_ESP32_DIGITALREAD_H
