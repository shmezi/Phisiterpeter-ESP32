//
// Created by Ezra Golombek on 03/12/2025.
//

#ifndef PHISITERPETER_ESP32_MOTOREXPRESSION_H
#define PHISITERPETER_ESP32_MOTOREXPRESSION_H
#include "expressions/Expression.h"


class MotorExpression : public Expression, public std::enable_shared_from_this<Scope> {


public:
    std::unique_ptr<Expression> a;
    std::unique_ptr<Expression> b;
    std::unique_ptr<Expression> speed;
    std::unique_ptr<Expression> encoderA;
    std::unique_ptr<Expression> encoderB;
    void move(bool direction);
    void stop();

    std::string expressionName() override;

    std::unique_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    MotorExpression(
        std::unique_ptr<Expression> a,
        std::unique_ptr<Expression> b,
        std::unique_ptr<Expression> speed,
        std::unique_ptr<Expression> encoderA,
        std::unique_ptr<Expression> encoderB

    );
};


#endif //PHISITERPETER_ESP32_MOTOREXPRESSION_H
