//
// Created by Ezra Golombek on 30/01/2026.
//

#include "../../../../include/factories/action/arithmetic/AbsExpressionFactory.h"

#include "expressions/action/arithmetic/AbsExpression.h"

std::string AbsExpressionFactory::startToken() {
    return "abs";
}

int AbsExpressionFactory::indexStart() {
    return 0;
}

int AbsExpressionFactory::paramSize() {
return 1;
}

std::unique_ptr<Expression> AbsExpressionFactory::generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                           std::shared_ptr<Scope> &scope) {
    return std::make_unique<AbsExpression>(std::move(arguments[0]));
}
