//
// Created by Ezra Golombek on 03/12/2025.
//

#include "../../../include/expressions/game/MotorExpression.h"

#include <algorithm>

#include "Utils.h"
#include "driver/gpio.h"
#include "expressions/value/NumberExpression.h"

void MotorExpression::move(bool direction) {
    auto pinA = static_cast<gpio_num_t>(dynamic_cast<NumberExpression *>(a.get())->contents);
    auto pinB = static_cast<gpio_num_t>(dynamic_cast<NumberExpression *>(b.get())->contents);
    if (!GPIO_IS_VALID_GPIO(pinA) || !GPIO_IS_VALID_GPIO(pinB)) {
        debug::error("Pin is invalid" );
    }
    gpio_set_direction(pinA, GPIO_MODE_OUTPUT);
    gpio_set_direction(pinB, GPIO_MODE_OUTPUT);
    gpio_set_level(pinA, !direction);
    gpio_set_level(pinB, direction);

}

void MotorExpression::stop() {
}

std::string MotorExpression::expressionName() {
    return "motor";
}

std::unique_ptr<Expression> MotorExpression::interpret(std::shared_ptr<Scope> scope) {
    return std::make_unique<MotorExpression>(
        (a->interpret(scope)),
        (b->interpret(scope)),
        (speed->interpret(scope)),
        (encoderA->interpret(scope)),
        (encoderB->interpret(scope)));
}

std::string MotorExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "A: " + a->interpertAsString(scope) + " B: " + b->interpertAsString(scope) + " Speed: " + speed->
           interpertAsString(scope) + " EncoderA: "
           + encoderA->interpertAsString(scope) + " EncoderB: " + encoderB->interpertAsString(scope);
}

MotorExpression::MotorExpression(std::unique_ptr<Expression> a, std::unique_ptr<Expression> b,
                                 std::unique_ptr<Expression> speed, std::unique_ptr<Expression> encoderA,
                                 std::unique_ptr<Expression> encoderB)
    : a(std::move(a)), b(std::move(b)), speed(std::move(speed)), encoderA(std::move(encoderA)),
      encoderB(std::move(encoderB)) {

}
