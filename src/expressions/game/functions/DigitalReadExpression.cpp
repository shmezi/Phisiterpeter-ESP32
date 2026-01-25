//
// Created by Ezra Golombek on 02/12/2025.
//

#include "../../../../include/expressions/game/functions/DigitalReadExpression.h"

#include <driver/gpio.h>
#include <hal/gpio_types.h>

#include "Utils.h"
#include "expressions/value/BooleanExpression.h"

std::string DigitalReadExpression::expressionName() {
    return "digitalRead";
}


std::shared_ptr<Expression> DigitalReadExpression::interpret(std::shared_ptr<Scope> scope) {
    const auto interpretedPin = pin->interpret(scope);
    auto expression = dynamic_cast<NumberExpression *>(interpretedPin.get());

    const  auto pinNumber = static_cast<int>(expression->contents);

    const auto gpio = static_cast<gpio_num_t>(pinNumber);
    if (!hasRun) {
        debug::log("Configured pin " + std::to_string(pinNumber) + " as an input!");
        gpio_set_direction(gpio, GPIO_MODE_INPUT);
        gpio_set_pull_mode(gpio,GPIO_PULLUP_ONLY);
        hasRun = true;
    }

    return std::make_unique<BooleanExpression>(gpio_get_level(gpio)==1);
}

std::string DigitalReadExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return this->interpret(scope)->interpertAsString(scope);
}
