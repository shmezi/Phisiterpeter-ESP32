//
// Created by Ezra Golombek on 07/12/2025.
//

#include "factories/game/AngleExpressionFactory.h"

#include <algorithm>

#include "expressions/game/AngleExpression.h"

std::string AngleExpressionFactory::startToken() {
    return "angle";
}

int AngleExpressionFactory::indexStart() {
    return 0;
}

int AngleExpressionFactory::paramSize() {
    return 1;
}

std::unique_ptr<Expression> AngleExpressionFactory::generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                             std::shared_ptr<Scope> &scope) {
    return std::make_unique<AngleExpression>(std::move(arguments[0]));
}
