//
// Created by Ezra Golombek on 28/01/2026.
//

#include "../../../../include/expressions/game/functions/EndActivityExpression.h"

#include <cstring>
#include <driver/uart.h>

#include "../../../../include/base/dovetail/DovetailCore.h"
#include "base/dovetail/DovetailClient.h"
#include "base/dovetail/DovetailMessageHandler.h"
#include "expressions/internal/VoidExpression.h"

std::string EndActivityExpression::expressionName() {
    return "endActivity";
}

std::shared_ptr<Expression> EndActivityExpression::interpret(std::shared_ptr<Scope> scope) {
    DovetailMessageHandler::endActivity();
    return std::make_shared<VoidExpression>();
}

std::string EndActivityExpression::interpretAsString(std::shared_ptr<Scope> scope) {
    return "sending an end activity!";
}
