//
// Created by Ezra Golombek on 03/12/2025.
//

#include "../../../include/expressions/action/control/MoveExpression.h"

#include "Utils.h"
#include "expressions/game/MotorExpression.h"
#include "expressions/internal/VoidExpression.h"
#include "expressions/value/BooleanExpression.h"

#include "expressions/value/NumberExpression.h"

#define PWM_FREQ_HZ (5000)
#define PWM_RESOLUTION_BITS (8) // 8-bit resolution (0-255)
#define PWM_CHANNEL LEDC_CHANNEL_1
#define PWM_TIMER LEDC_TIMER_0
#

std::string MoveExpression::expressionName() {
    return "motor";
}

std::unique_ptr<Expression> MoveExpression::interpret(std::shared_ptr<Scope> scope) {
    const auto motorExpression = motor->interpret(scope);
    auto castMotor = dynamic_cast<MotorExpression *>(motorExpression.get());

    castMotor->move(dynamic_cast<NumberExpression *>(speed->interpret(scope).get())->contents);


    return std::make_unique<VoidExpression>();
}

std::string MoveExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "motor spin woooooo";
}

MoveExpression::MoveExpression(std::unique_ptr<Expression> motor,
                               std::unique_ptr<Expression> speed) : motor(std::move(motor)),
                                                                        speed(std::move(speed)) {
}
