//
// Created by Ezra Golombek on 31/01/2026.
//

#ifndef PHISITERPETER_ESP32_RESETROTATIONS_H
#define PHISITERPETER_ESP32_RESETROTATIONS_H
#include <algorithm>

#include "expressions/Expression.h"


class ResetRotationsExpression : public Expression {
    std::unique_ptr<Expression> motor;

public:
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    explicit ResetRotationsExpression(std::unique_ptr<Expression> motor) : motor(std::move(motor)){

    };
};


#endif //PHISITERPETER_ESP32_RESETROTATIONS_H
