//
// Created by Ezra Golombek on 28/01/2026.
//

#include "../../../../include/expressions/game/functions/EndActivityExpression.h"

#include <cstring>
#include <driver/uart.h>

#include "expressions/internal/VoidExpression.h"

std::string EndActivityExpression::expressionName() {
    return "endActivity";
}

std::shared_ptr<Expression> EndActivityExpression::interpret(std::shared_ptr<Scope> scope) {
    auto rawMessageToSend = "s";

    uart_write_bytes(UART_NUM_2, rawMessageToSend, strlen(rawMessageToSend));

    return std::make_shared<VoidExpression>();
}

std::string EndActivityExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "sending an end activity!";
}
