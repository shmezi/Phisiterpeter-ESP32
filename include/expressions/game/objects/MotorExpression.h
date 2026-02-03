//
// Created by Ezra Golombek on 03/12/2025.
//

#ifndef PHISITERPETER_ESP32_MOTOREXPRESSION_H
#define PHISITERPETER_ESP32_MOTOREXPRESSION_H
#include <soc/gpio_num.h>

#include "expressions/Expression.h"


class MotorExpression : public Expression, public std::enable_shared_from_this<MotorExpression> {
public:
    gpio_num_t bActualPin;
    std::unique_ptr<Expression> a;
    std::unique_ptr<Expression> b;
    std::unique_ptr<Expression> speed;
    std::unique_ptr<Expression> encoderA;
    std::unique_ptr<Expression> encoderB;
    volatile int rotations;
    int requestRotation = -1;

    void move(int speedValue) const;

    void stop();

    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    void rotate();

    void rotateUntilRotation(int rotation, int speed);

    void initEncoder() ;

    MotorExpression(
        std::unique_ptr<Expression> a,
        std::unique_ptr<Expression> b,
        std::unique_ptr<Expression> speed,
        std::unique_ptr<Expression> encoderA,
        std::unique_ptr<Expression> encoderB

    );
};


#endif //PHISITERPETER_ESP32_MOTOREXPRESSION_H
