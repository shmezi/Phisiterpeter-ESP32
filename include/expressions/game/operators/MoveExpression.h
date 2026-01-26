//
// Created by Ezra Golombek on 03/12/2025.
//

#ifndef PHISITERPETER_ESP32_MOVEEXPRESSION_H
#define PHISITERPETER_ESP32_MOVEEXPRESSION_H
#include "expressions/BaseExpression.h"


class MoveExpression : public BaseExpression {
    std::unique_ptr<BaseExpression> motor;
    std::unique_ptr<BaseExpression> speed;

public:
    std::string expressionName() override;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    MoveExpression(std::unique_ptr<BaseExpression> motor, std::unique_ptr<BaseExpression> speed);
};


#endif //PHISITERPETER_ESP32_MOVEEXPRESSION_H
