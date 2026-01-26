//
// Created by Ezra Golombek on 03/12/2025.
//

#include "../../../../include/factories/game/operators/MoveExpressionFactory.h"

#include <algorithm>

#include "../../../../include/expressions/game/operators/MoveExpression.h"

std::string MoveExpressionFactory::startToken() {
    return "move";
}

int MoveExpressionFactory::indexStart() {
    return 0;
}

int MoveExpressionFactory::paramSize() {
    return 2;
}

std::unique_ptr<BaseExpression> MoveExpressionFactory::generate(std::deque<std::unique_ptr<BaseExpression>> &arguments,
    std::shared_ptr<Scope> &scope) {
    return std::make_unique<MoveExpression>(std::move(arguments[0]),std::move(arguments[1]));
}
