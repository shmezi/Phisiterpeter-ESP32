//
// Created by Ezra Golombek on 10/12/2025.
//

#include "../../../../include/expressions/game/functions/SendResultExpression.h"

#include <algorithm>
#include <cstring>
#include <driver/uart.h>

#include "expressions/internal/VoidExpression.h"

std::string SendResultExpression::expressionName() {
    return "sendResult";
}

std::shared_ptr<Expression> SendResultExpression::interpret(std::shared_ptr<Scope> scope) {
    const std::string message = name->interpertAsString(scope) + " " + value->interpertAsString(scope) + "\n";
    const char *cMessage = message.c_str();
    uart_write_bytes(UART_NUM_2, cMessage, strlen(cMessage));
    return std::make_shared<VoidExpression>();
}

std::string SendResultExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}

SendResultExpression::SendResultExpression(std::unique_ptr<Expression> name, std::unique_ptr<Expression> value) : name(
        std::move(name)), value(std::move(value)) {
}
