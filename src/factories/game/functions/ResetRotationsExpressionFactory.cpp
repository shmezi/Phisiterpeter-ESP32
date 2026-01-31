//
// Created by Ezra Golombek on 31/01/2026.
//

#include "../../../../include/factories/game/functions/ResetRotationsExpressionFactory.h"

#include "expressions/game/functions/ResetRotationsExpression.h"

std::string ResetRotationsExpressionFactory::startToken() {
    return "reset";
}

int ResetRotationsExpressionFactory::indexStart() {
    return 0;
}

int ResetRotationsExpressionFactory::paramSize() {
    return 1;
}

std::unique_ptr<Expression> ResetRotationsExpressionFactory::generate(
    std::deque<std::unique_ptr<Expression> > &arguments, std::shared_ptr<Scope> &scope) {
    return std::make_unique<ResetRotationsExpression>(std::move(arguments[0]));
}
