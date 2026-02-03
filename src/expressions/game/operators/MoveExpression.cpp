//
// Created by Ezra Golombek on 03/12/2025.
//

#include "../../../../include/expressions/game/operators/MoveExpression.h"

#include "Utils.h"
#include "../../../../include/expressions/game/objects/MotorExpression.h"
#include "expressions/internal/VoidExpression.h"
#include "expressions/value/BooleanExpression.h"

#include "expressions/value/NumberExpression.h"

#define PWM_FREQ_HZ (5000)
#define PWM_RESOLUTION_BITS (8) // 8-bit resolution (0-255)
#define PWM_CHANNEL LEDC_CHANNEL_1
#define PWM_TIMER LEDC_TIMER_0
#

std::string MoveExpression::expressionName() {
    return "move";
}

std::shared_ptr<Expression> MoveExpression::interpret(std::shared_ptr<Scope> scope) {
    auto evaluatedMotor = std::dynamic_pointer_cast<MotorExpression>(motor->interpret(scope));

    auto evaluatedSpeed = std::dynamic_pointer_cast<NumberExpression>(speed->interpret(scope));

    evaluatedMotor->move(static_cast<int>(evaluatedSpeed->contents));


    return std::make_unique<VoidExpression>();
}

std::string MoveExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "motor spin woooooo";
}

MoveExpression::MoveExpression(std::unique_ptr<Expression> motor,
                               std::unique_ptr<Expression> speed) : motor(std::move(motor)),
                                                                    speed(std::move(speed)) {
}
