//
// Created by Ezra Golombek on 07/12/2025.
//

#ifndef PHISITERPETER_ESP32_ROTATIONSEXPRESSION_H
#define PHISITERPETER_ESP32_ROTATIONSEXPRESSION_H
#include "expressions/Expression.h"


class RotationsExpression  : public Expression{
    std::unique_ptr<Expression> motor;
public:
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
    RotationsExpression(std::unique_ptr<Expression> motor);
};


#endif //PHISITERPETER_ESP32_ROTATIONSEXPRESSION_H