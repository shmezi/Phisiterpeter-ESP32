//
// Created by Ezra Golombek on 06/11/2025.
//


#include "factories/action/control/ReturnExpressionFactory.h"

#include "../../../../include/expressions/action/control/ReturnExpression.h"


std::string ReturnExpressionFactory::startToken() {
    return "return";
}

int ReturnExpressionFactory::indexStart() {
    return 0;
}

int ReturnExpressionFactory::paramSize() {
    return 1;
}

std::unique_ptr<Expression> ReturnExpressionFactory::generate(
    std::deque<std::unique_ptr<Expression> > &arguments, std::shared_ptr<Scope> &scope) {
    return make_unique<ReturnExpression>(std::move(arguments[0]));
}
