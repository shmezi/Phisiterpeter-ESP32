//
// Created by Ezra Golombek on 03/12/2025.
//

#ifndef PHISITERPETER_ESP32_MOTOREXPRESSION_H
#define PHISITERPETER_ESP32_MOTOREXPRESSION_H
#include <soc/gpio_num.h>

#include "expressions/BaseExpression.h"


class MotorExpression : public BaseExpression, public std::enable_shared_from_this<MotorExpression> {
public:
    gpio_num_t bActualPin;
    std::unique_ptr<BaseExpression> a;
    std::unique_ptr<BaseExpression> b;
    std::unique_ptr<BaseExpression> speed;
    std::unique_ptr<BaseExpression> encoderA;
    std::unique_ptr<BaseExpression> encoderB;
    volatile int rotations;

    void move(int speedValue) const;

    void stop();

    std::string expressionName() override;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    void rotate();

    void initEncoder() ;

    MotorExpression(
        std::unique_ptr<BaseExpression> a,
        std::unique_ptr<BaseExpression> b,
        std::unique_ptr<BaseExpression> speed,
        std::unique_ptr<BaseExpression> encoderA,
        std::unique_ptr<BaseExpression> encoderB

    );
};


#endif //PHISITERPETER_ESP32_MOTOREXPRESSION_H
