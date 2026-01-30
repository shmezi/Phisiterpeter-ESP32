//
// Created by Ezra Golombek on 10/12/2025.
//

#include "../../../../include/expressions/game/functions/SendResultExpression.h"

#include <algorithm>
#include <cstring>
#include <driver/uart.h>

#include "../../../../../../.platformio/packages/toolchain-riscv32-esp/riscv32-esp-elf/include/c++/14.2.0/queue"
#include "expressions/internal/VoidExpression.h"
std::string SendResultExpression::nextMessage[3];
std::string SendResultExpression::prevMessage[3];
std::string SendResultExpression::expressionName() {
    return "sendResult";
}


std::shared_ptr<Expression> SendResultExpression::interpret(std::shared_ptr<Scope> scope) {
    const auto id = name->interpertAsString(scope);
    // int idInt = id == "a" ? 0 : 1;
    // if (id == "c") idInt = 2;
    const std::string message = id + " " + value->interpertAsString(scope) + "\n";

    // nextMessage[idInt] = message;
    const auto cMessage = message.c_str();

    uart_write_bytes(UART_NUM_2, cMessage, strlen(cMessage));
    return std::make_shared<VoidExpression>();
}

std::string SendResultExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}

SendResultExpression::SendResultExpression(std::unique_ptr<Expression> name, std::unique_ptr<Expression> value) : name(
        std::move(name)), value(std::move(value)) {
}
