//
// Created by Ezra Golombek on 11/11/2025.
//


#include "factories/action/bool/NotExpressionFactory.h"

#include <deque>
#include <string>

#include "expressions/action/bool/NotExpression.h"

class BaseExpression;

std::string NotExpressionFactory::startToken() {
    return "not";

}

int NotExpressionFactory::indexStart() {
    return 0;
}

int NotExpressionFactory::paramSize() {
    return 1;
}

std::unique_ptr<BaseExpression> NotExpressionFactory::generate(std::deque<std::unique_ptr<BaseExpression> > &arguments,
                                                           std::shared_ptr<Scope> &scope) {
    return std::make_unique<NotExpression>(std::move(arguments[0]));
}
