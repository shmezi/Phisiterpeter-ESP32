//
// Created by Ezra Golombek on 07/12/2025.
//

#include "factories/game/RotationsExpressionFactory.h"

#include <algorithm>

#include "expressions/game/RotationsExpression.h"

std::string RotationsExpressionFactory::startToken() {
    return "rotations";
}

int RotationsExpressionFactory::indexStart() {
    return 0;
}

int RotationsExpressionFactory::paramSize() {
    return 1;
}

std::unique_ptr<Expression> RotationsExpressionFactory::generate(std::deque<std::unique_ptr<Expression>> &arguments,
    std::shared_ptr<Scope> &scope) {
    return std::make_unique<RotationsExpression>(std::move(arguments[0]));
}
