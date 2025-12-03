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
    gpio_set_direction(gpio, GPIO_MODE_INPUT);
    gpio_set_pull_mode(gpio,GPIO_PULLUP_ONLY);
    return std::make_unique<BooleanExpression>(gpio_get_level(gpio)==1);
}

std::string DigitalReadExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return this->interpret(scope)->interpertAsString(scope);
}