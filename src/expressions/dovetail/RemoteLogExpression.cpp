//
// Created by Ezra Golombek on 12/06/2026.
//

#include "../../../include/expressions/dovetail/RemoteLogExpression.h"

#include "base/dovetail/DovetailMessageHandler.h"
#include "expressions/internal/VoidExpression.h"
#include "expressions/value/TextExpression.h"

std::string RemoteLogExpression::expressionName() {
    return "remoteLog";
}

std::shared_ptr<Expression> RemoteLogExpression::interpret(std::shared_ptr<Scope> scope) {
    DovetailMessageHandler::sendLog(contents->interpretAsString(scope));
    return std::make_shared<VoidExpression>();
}
