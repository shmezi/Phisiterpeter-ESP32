//
// Created by Ezra Golombek on 10/12/2025.
//

#include "../../../../include/expressions/game/functions/SendResultExpression.h"

#include <algorithm>
#include <cstring>

#include "../../../../../../.platformio/packages/toolchain-riscv32-esp/riscv32-esp-elf/include/c++/14.2.0/queue"
#include "../../../../include/base/dovetail/DovetailCore.h"
#include "expressions/internal/VoidExpression.h"
std::string SendResultExpression::nextMessage[3];
std::string SendResultExpression::prevMessage[3];

std::string SendResultExpression::expressionName() {
    return "sendResult";
}


std::shared_ptr<Expression> SendResultExpression::interpret(std::shared_ptr<Scope> scope) {
    const auto id = name->interpertAsString(scope);

    const std::string v = (value->interpertAsString(scope));

    DovetailCore::sendGetRequest("sendResult?val=" + v + "&slot=" + id);
    return std::make_shared<VoidExpression>();
}

std::string SendResultExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}

SendResultExpression::SendResultExpression(std::unique_ptr<Expression> name, std::unique_ptr<Expression> value) : name(
        std::move(name)), value(std::move(value)) {
}
