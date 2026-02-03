//
// Created by Ezra Golombek on 31/01/2026.
//

#ifndef PHISITERPETER_ESP32_ROTATEMOTORBYEXPRESSION_H
#define PHISITERPETER_ESP32_ROTATEMOTORBYEXPRESSION_H
#include <algorithm>

#include "expressions/Expression.h"


class RotateMotorByExpression : public Expression {
    std::unique_ptr<Expression> motor;
    std::unique_ptr<Expression> speed;
    std::unique_ptr<Expression> rotateTo;

public:
    std::string expressionName() override;

    RotateMotorByExpression(
        std::unique_ptr<Expression> motor,

        std::unique_ptr<Expression> rotateTo,

        std::unique_ptr<Expression> speed);

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;
};


#endif //PHISITERPETER_ESP32_ROTATEMOTORBYEXPRESSION_H
