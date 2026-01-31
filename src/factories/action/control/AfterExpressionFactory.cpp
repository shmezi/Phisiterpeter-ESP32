//
// Created by Ezra Golombek on 31/01/2026.
//

#include "factories/action/control/AfterExpressionFactory.h"

#include "expressions/action/control/AfterExpression.h"

std::string AfterExpressionFactory::startToken() {
    return "after";
}

int AfterExpressionFactory::indexStart() {
return 0;
}

int AfterExpressionFactory::paramSize() {
return 2;
}

std::unique_ptr<Expression> AfterExpressionFactory::generate(std::deque<std::unique_ptr<Expression>> &arguments,
    std::shared_ptr<Scope> &scope) {
return std::make_unique<AfterExpression>(std::move(arguments[0]),std::move(arguments[1]));
}
