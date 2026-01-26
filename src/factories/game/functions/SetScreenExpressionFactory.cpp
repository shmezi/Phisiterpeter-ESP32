//
// Created by Ezra Golombek on 22/01/2026.
//


#include "factories/game/functions/SetScreenExpressionFactory.h"

#include <algorithm>

#include "expressions/game/functions/SetScreenExpression.h"


std::string SetScreenExpressionFactory::startToken() {
    return "screen";
}

int SetScreenExpressionFactory::indexStart() {
    return 0;
}

int SetScreenExpressionFactory::paramSize() {
    return 1;
}

std::unique_ptr<BaseExpression> SetScreenExpressionFactory::generate(
    std::deque<std::unique_ptr<BaseExpression> > &arguments,
    std::shared_ptr<Scope> &scope) {
    return std::make_unique<SetScreenExpression>(std::move(arguments[0]));
}
