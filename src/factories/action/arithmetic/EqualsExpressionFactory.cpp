//
// Created by Ezra Golombek on 30/11/2025.
//

#include "../../../../include/factories/action/arithmetic/EqualsExpressionFactory.h"

#include "expressions/action/arithmetic/EqualsExpression.h"

std::unique_ptr<BaseExpression> EqualsExpressionFactory::generate(std::deque<std::unique_ptr<BaseExpression> > &arguments, std::shared_ptr<Scope> &scope) {

    return std::make_unique<EqualsExpression>(std::move(arguments[0]), std::move(arguments[1]));
}

int EqualsExpressionFactory::paramSize() {
    return 2;
}

std::string EqualsExpressionFactory::startToken() {
    return "==";
}

int EqualsExpressionFactory::indexStart() {
    return -1;
}
