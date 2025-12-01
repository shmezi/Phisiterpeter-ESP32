//
// Created by Ezra Golombek on 08/11/2025.
//

#include "factories/action/bool/OrExpressionFactory.h"

#include <string>

#include "expressions/action/bool/OrExpression.h"

std::string OrExpressionFactory::startToken() {
    return "or";
}

int OrExpressionFactory::indexStart() {
    return -1;
}

int OrExpressionFactory::paramSize() {
    return 2;
}

std::unique_ptr<Expression> OrExpressionFactory::generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                          std::shared_ptr<Scope> &scope) {
    return std::make_unique<OrExpression>(std::move(arguments[0]), std::move(arguments[1]));
}
