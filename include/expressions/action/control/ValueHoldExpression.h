//
// Created by Ezra Golombek on 07/12/2025.
//

#ifndef PHISITERPETER_ESP32_VALUEHOLDEXPRESSION_H
#define PHISITERPETER_ESP32_VALUEHOLDEXPRESSION_H
#include "expressions/BaseExpression.h"


class ValueHoldExpression : public BaseExpression{
    std::shared_ptr<BaseExpression> expression;
public:
    std::string expressionName() override;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
    ValueHoldExpression(const std::shared_ptr<BaseExpression> &expression);
};


#endif //PHISITERPETER_ESP32_VALUEHOLDEXPRESSION_H