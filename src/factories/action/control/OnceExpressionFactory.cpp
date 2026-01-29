//
// Created by Ezra Golombek on 29/01/2026.
//

#include "../../../../include/factories/action/control/OnceExpressionFactory.h"

#include "expressions/action/control/OnceExpression.h"

std::string OnceExpressionFactory::startToken() {
    return "once";
}

int OnceExpressionFactory::indexStart() {
    return 0;
}

int OnceExpressionFactory::paramSize() {
    return 2;
}

std::unique_ptr<Expression> OnceExpressionFactory::generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                            std::shared_ptr<Scope> &scope) {
    return std::make_unique<OnceExpression>(std::move(arguments[0]), std::move(arguments[1]));
}
