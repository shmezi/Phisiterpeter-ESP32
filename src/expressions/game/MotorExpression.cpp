//
// Created by Ezra Golombek on 03/12/2025.
//

#include "../../../include/expressions/game/MotorExpression.h"

#include <algorithm>

#include "Utils.h"
#include "driver/gpio.h"
#include "expressions/value/NumberExpression.h"
#include "driver/mcpwm.h"
#include "esp_log.h"

void MotorExpression::move(const int speedValue) const {
    auto pinA = static_cast<gpio_num_t>(dynamic_cast<NumberExpression *>(a.get())->contents);
    auto pinB = static_cast<gpio_num_t>(dynamic_cast<NumberExpression *>(b.get())->contents);
    auto pinSpeed = static_cast<gpio_num_t>(dynamic_cast<NumberExpression *>(speed.get())->contents);

    if (!GPIO_IS_VALID_GPIO(pinA) || !GPIO_IS_VALID_GPIO(pinB)) {
        debug::error("Pin is invalid");
    }
    gpio_set_direction(pinA, GPIO_MODE_OUTPUT);
    gpio_set_direction(pinB, GPIO_MODE_OUTPUT);
    gpio_set_level(pinA, speedValue > 0);
    gpio_set_level(pinB, speedValue < 0);
    // Setup GPIO 18 for MCPWM0A
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, pinSpeed);

    // Init MCPWM with 1 kHz frequency, 50% duty
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 1000; // 1 kHz
    pwm_config.cmpr_a = speedValue; // 50% duty cycle
    pwm_config.cmpr_b = 0.0; // unused
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;

    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);
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
