//
// Created by Ezra Golombek on 03/12/2025.
//

#ifndef PHISITERPETER_ESP32_MOVEEXPRESSION_H
#define PHISITERPETER_ESP32_MOVEEXPRESSION_H
#include "expressions/Expression.h"


class MoveExpression : public Expression {
    std::unique_ptr<Expression> motor;
    std::unique_ptr<Expression> speed;

public:
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    MoveExpression(std::unique_ptr<Expression> motor, std::unique_ptr<Expression> speed);
};


#endif //PHISITERPETER_ESP32_MOVEEXPRESSION_H
