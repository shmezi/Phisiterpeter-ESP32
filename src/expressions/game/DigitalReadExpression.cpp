//
// Created by Ezra Golombek on 02/12/2025.
//

#include "../../../include/expressions/game/DigitalReadExpression.h"

#include <driver/gpio.h>
#include <hal/gpio_types.h>

#include "expressions/value/BooleanExpression.h"

std::string DigitalReadExpression::expressionName() {
    return "digitalRead";
}

std::unique_ptr<Expression> DigitalReadExpression::interpret(std::shared_ptr<Scope> scope) {
    auto expression = dynamic_cast<NumberExpression *>(pin.get());

    const auto gpio = static_cast<gpio_num_t>(expression->contents);
    gpio_set_direction(static_cast<gpio_num_t>(expression->contents), GPIO_MODE_INPUT);
    return std::make_unique<BooleanExpression>(gpio_get_level(gpio));
}

std::string DigitalReadExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return this->interpret(scope)->interpertAsString(scope);
}