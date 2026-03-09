//
// Created by Ezra Golombek on 03/02/2026.
//

#ifndef PHISITERPETER_ESP32_WRAP360EXPRESSION_H
#define PHISITERPETER_ESP32_WRAP360EXPRESSION_H
#include "expressions/Expression.h"


class Wrap360Expression : public Expression {
    std::unique_ptr<Expression> inputNumber;

public:
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    explicit Wrap360Expression(std::unique_ptr<Expression> inputNumber) : inputNumber(std::move(inputNumber)) {
    }
};


#endif //PHISITERPETER_ESP32_WRAP360EXPRESSION_H
