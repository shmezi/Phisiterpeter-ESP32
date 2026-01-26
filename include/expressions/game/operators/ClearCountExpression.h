//
// Created by Ezra Golombek on 11/12/2025.
//

#ifndef PHISITERPETER_ESP32_CLEARCOUNTEXPRESSION_H
#define PHISITERPETER_ESP32_CLEARCOUNTEXPRESSION_H
#include "expressions/BaseExpression.h"


class ClearCountExpression : public BaseExpression{
    std::unique_ptr<BaseExpression> motor;
public:
    std::string expressionName() override;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
    explicit ClearCountExpression (std::unique_ptr<BaseExpression> motor);
};


#endif //PHISITERPETER_ESP32_CLEARCOUNTEXPRESSION_H