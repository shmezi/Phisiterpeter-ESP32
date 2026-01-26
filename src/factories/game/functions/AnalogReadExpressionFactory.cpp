//
// Created by Ezra Golombek on 26/01/2026.
//

#include "../../../../include/factories/game/functions/AnalogReadExpressionFactory.h"

#include <algorithm>

#include "expressions/game/functions/AnalogReadExpression.h"

std::string AnalogReadExpressionFactory::startToken() {
    return "analog";
}

int AnalogReadExpressionFactory::indexStart() {
    return 0;
}

int AnalogReadExpressionFactory::paramSize() {
    return 1;
}

std::unique_ptr<Expression> AnalogReadExpressionFactory::generate(std::deque<std::unique_ptr<Expression>> &arguments,
    std::shared_ptr<Scope> &scope) {
    return std::make_unique<AnalogReadExpression>(std::move(arguments[0]));
}
