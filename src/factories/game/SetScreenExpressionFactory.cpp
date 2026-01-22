//
// Created by Ezra Golombek on 22/01/2026.
//

#include "../../../include/factories/game/SetScreenExpressionFactory.h"

#include <algorithm>

#include "expressions/game/SetScreenExpression.h"

std::string SetScreenExpressionFactory::startToken() {
    return "screen";
}

int SetScreenExpressionFactory::indexStart() {
    return 0;
}

int SetScreenExpressionFactory::paramSize() {
    return 1;
}

std::unique_ptr<Expression> SetScreenExpressionFactory::generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                                 std::shared_ptr<Scope> &scope) {
    return std::make_unique<SetScreenExpression>(std::move(arguments[0]));
}
