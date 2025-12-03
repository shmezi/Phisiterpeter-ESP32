//
// Created by Ezra Golombek on 03/12/2025.
//

#include "../../../include/factories/game/MoveExpressionFactory.h"

#include <algorithm>

#include "expressions/action/control/MoveExpression.h"

std::string MoveExpressionFactory::startToken() {
    return "move";
}

int MoveExpressionFactory::indexStart() {
    return 0;
}

int MoveExpressionFactory::paramSize() {
    return 2;
}

std::unique_ptr<Expression> MoveExpressionFactory::generate(std::deque<std::unique_ptr<Expression>> &arguments,
    std::shared_ptr<Scope> &scope) {
    return std::make_unique<MoveExpression>(std::move(arguments[0]),std::move(arguments[1]));
}
