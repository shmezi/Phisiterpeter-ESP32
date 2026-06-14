//
// Created by Ezra Golombek on 10/12/2025.
//

#include "../../../../include/expressions/game/functions/SendResultExpression.h"

#include <algorithm>
#include <cstring>

#include "../../../../../../.platformio/packages/toolchain-riscv32-esp/riscv32-esp-elf/include/c++/14.2.0/queue"
#include "../../../../include/base/dovetail/DovetailCore.h"
#include "base/dovetail/DovetailClient.h"
#include "base/dovetail/DovetailMessageHandler.h"
#include "expressions/internal/VoidExpression.h"
std::string SendResultExpression::nextMessage[3];
std::string SendResultExpression::prevMessage[3];

std::string SendResultExpression::expressionName() {
    return "sendResult";
}


std::shared_ptr<Expression> SendResultExpression::interpret(std::shared_ptr<Scope> scope) {
    const auto id = name->interpretAsString(scope);

    const std::string v = (value->interpretAsString(scope));

    DovetailMessageHandler::sendResult(id, v);

    return std::make_shared<VoidExpression>();
}

std::string SendResultExpression::interpretAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpretAsString(scope);
}

SendResultExpression::SendResultExpression(std::unique_ptr<Expression> name, std::unique_ptr<Expression> value) : name(
        std::move(name)), value(std::move(value)) {
}
