//
// Created by Ezra Golombek on 11/12/2025.
//

#include "../../../include/factories/game/functions/OnEventExpressionFactory.h"

#include <algorithm>

#include "../../../include/expressions/game/functions/OnEventExpression.h"

std::string OnEventExpressionFactory::startToken() {
    return "on";
}

int OnEventExpressionFactory::indexStart() {
    return 0;
}

int OnEventExpressionFactory::paramSize() {
    return 2; // on "event" { }
}

std::unique_ptr<Expression> OnEventExpressionFactory::generate(std::deque<std::unique_ptr<Expression>> &arguments,
    std::shared_ptr<Scope> &scope) {
    return std::make_unique<OnEventExpression>(std::move(arguments[0]),std::move(arguments[1]));
}
