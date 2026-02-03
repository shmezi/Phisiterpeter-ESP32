//
// Created by Ezra Golombek on 03/02/2026.
//

#include "../../../../include/factories/game/functions/DegreesExpressionFactory.h"

#include "expressions/game/functions/DegreesExpression.h"


std::string DegreesExpressionFactory::startToken() {
    return "degrees";
}

int DegreesExpressionFactory::indexStart() {
    return 0;
}

int DegreesExpressionFactory::paramSize() {
    return 1;
}

std::unique_ptr<Expression> DegreesExpressionFactory::generate(
    std::deque<std::unique_ptr<Expression> > &arguments,
    std::shared_ptr<Scope> &scope) {
    return std::make_unique<DegreesExpression>(std::move(arguments[0]));
}
