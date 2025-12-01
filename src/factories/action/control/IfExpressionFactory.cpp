//
// Created by Ezra Golombek on 08/11/2025.
//

#include "factories/action/control/IfExpressionFactory.h"

#include "expressions/action/control/IfExpression.h"


int IfExpressionFactory::indexStart() {
    return 0;
}

int IfExpressionFactory::paramSize() {
    return 2;
}

std::string IfExpressionFactory::startToken() {
    return "if";
}

std::unique_ptr<Expression> IfExpressionFactory::generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                          std::shared_ptr<Scope> &scope) {
    return std::make_unique<IfExpression>(std::move(arguments[0]), std::move(arguments[1]));
}
