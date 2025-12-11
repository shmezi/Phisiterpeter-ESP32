//
// Created by Ezra Golombek on 11/12/2025.
//

#include "../../../include/factories/game/ClearCountExpressionFactory.h"

#include <algorithm>

#include "expressions/game/ClearCountExpression.h"

std::string ClearCountExpressionFactory::startToken() {
    return "reset";
}

int ClearCountExpressionFactory::indexStart() {
    return 0;
}

int ClearCountExpressionFactory::paramSize() {
    return 1;
}

std::unique_ptr<Expression> ClearCountExpressionFactory::generate(std::deque<std::unique_ptr<Expression>> &arguments,
    std::shared_ptr<Scope> &scope) {
    return std::make_unique<ClearCountExpression>(std::move(arguments[0]));
}
