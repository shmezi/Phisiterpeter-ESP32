//
// Created by Ezra Golombek on 07/12/2025.
//

#ifndef PHISITERPETER_ESP32_VALUEHOLDEXPRESSION_H
#define PHISITERPETER_ESP32_VALUEHOLDEXPRESSION_H
#include "expressions/Expression.h"


class ValueHoldExpression : public Expression{
    std::shared_ptr<Expression> expression;
public:
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
    ValueHoldExpression(const std::shared_ptr<Expression> &expression);
};


#endif //PHISITERPETER_ESP32_VALUEHOLDEXPRESSION_H