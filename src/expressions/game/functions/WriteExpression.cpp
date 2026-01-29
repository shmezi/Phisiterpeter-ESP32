//
// Created by Ezra Golombek on 04/12/2025.
//

#include "../../../../include/expressions/game/functions/WriteExpression.h"

#include <algorithm>
#include <driver/gpio.h>

#include "expressions/internal/VoidExpression.h"
#include "expressions/value/BooleanExpression.h"
#include "expressions/value/NumberExpression.h"

WriteExpression::WriteExpression(std::unique_ptr<Expression> pin,
                                 std::unique_ptr<Expression> value) : pin(std::move(pin)), value(std::move(value)) {
}

std::string WriteExpression::expressionName() {
    return "write";
}

std::shared_ptr<Expression> WriteExpression::interpret(std::shared_ptr<Scope> scope) {
    const auto pinNumber = static_cast<gpio_num_t>(dynamic_cast<NumberExpression *>(pin->interpret(scope).get())->
        contents);
    const auto writeableValue = dynamic_cast<BooleanExpression *>(value->interpret(scope).get())->contents;

    gpio_set_direction(pinNumber, GPIO_MODE_OUTPUT);
    gpio_set_level(pinNumber, writeableValue ? 1 : 0);
    return std::make_unique<VoidExpression>();
}

std::string WriteExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "Writing to pin: " + pin->interpertAsString(scope);
}
