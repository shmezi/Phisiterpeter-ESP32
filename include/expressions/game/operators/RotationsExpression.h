//
// Created by Ezra Golombek on 07/12/2025.
//

#ifndef PHISITERPETER_ESP32_ROTATIONSEXPRESSION_H
#define PHISITERPETER_ESP32_ROTATIONSEXPRESSION_H
#include "expressions/BaseExpression.h"


class RotationsExpression  : public BaseExpression{
    std::unique_ptr<BaseExpression> motor;
public:
    std::string expressionName() override;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
    RotationsExpression(std::unique_ptr<BaseExpression> motor);
};


#endif //PHISITERPETER_ESP32_ROTATIONSEXPRESSION_H