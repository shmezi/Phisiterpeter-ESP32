//
// Created by Ezra Golombek on 03/02/2026.
//

#ifndef PHISITERPETER_ESP32_DEGREESEXPRESSION_H
#define PHISITERPETER_ESP32_DEGREESEXPRESSION_H
#include "expressions/Expression.h"


class DegreesExpression : public Expression {
    std::unique_ptr<Expression> motor;
public:
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;
    explicit DegreesExpression( std::unique_ptr<Expression> motor) : motor(std::move(motor)){}
};


#endif //PHISITERPETER_ESP32_DEGREESEXPRESSION_H