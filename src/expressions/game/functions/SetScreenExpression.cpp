//
// Created by Ezra Golombek on 22/01/2026.
//


#include "expressions/game/functions/SetScreenExpression.h"

#include <algorithm>


#include "../../../../include/base/dovetail/DovetailCore.h"
#include "base/dovetail/DovetailClient.h"
#include "expressions/internal/VoidExpression.h"

std::string SetScreenExpression::expressionName() {
    return "screen";
}

std::shared_ptr<Expression> SetScreenExpression::interpret(std::shared_ptr<Scope> scope) {
    const auto screenName = screen->interpertAsString(scope);
    DovetailClient::sendGetRequest("screen?id=" + screenName);
    return std::make_shared<VoidExpression>();
}

std::string SetScreenExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "Set screen!";
}

SetScreenExpression::SetScreenExpression(std::unique_ptr<Expression> screen) {
    this->screen = std::move(screen);
}
