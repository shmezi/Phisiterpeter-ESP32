//
// Created by Ezra Golombek on 22/01/2026.
//


#include "expressions/game/functions/SetScreenExpression.h"

#include <algorithm>
#include <cstring>
#include <driver/uart.h>

#include "expressions/internal/VoidExpression.h"

std::string SetScreenExpression::expressionName() {
    return "screen";
}

std::shared_ptr<BaseExpression> SetScreenExpression::interpret(std::shared_ptr<Scope> scope) {
    const auto screenName = screen->interpertAsString(scope);
    int value = 1;
    if (screenName == "swing" || screenName == "ferriswheel")
        value = 2;
    if (screenName == "blackmamba")
        value = 3;
    const auto screenId = std::to_string(value);
    const char *rawMessageToSend = screenId.c_str();

    uart_write_bytes(UART_NUM_2, rawMessageToSend, strlen(rawMessageToSend));

    return std::make_shared<VoidExpression>();
}

std::string SetScreenExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "Set screen!";
}

SetScreenExpression::SetScreenExpression(std::unique_ptr<BaseExpression> screen) {
    this->screen = std::move(screen);
}
