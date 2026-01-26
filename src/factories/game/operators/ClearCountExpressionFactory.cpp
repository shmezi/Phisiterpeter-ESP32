//
// Created by Ezra Golombek on 11/12/2025.
//

#include "../../../../include/factories/game/operators/ClearCountExpressionFactory.h"

#include <algorithm>

#include "../../../../include/expressions/game/operators/ClearCountExpression.h"

std::string ClearCountExpressionFactory::startToken() {
    return "reset";
}

int ClearCountExpressionFactory::indexStart() {
    return 0;
}

int ClearCountExpressionFactory::paramSize() {
    return 1;
}

std::unique_ptr<BaseExpression> ClearCountExpressionFactory::generate(std::deque<std::unique_ptr<BaseExpression>> &arguments,
    std::shared_ptr<Scope> &scope) {
    return std::make_unique<ClearCountExpression>(std::move(arguments[0]));
}
