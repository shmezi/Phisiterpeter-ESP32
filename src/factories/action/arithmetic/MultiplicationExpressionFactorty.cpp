//
// Created by Ezra Golombek on 30/11/2025.
//

#include "../../../../include/factories/action/arithmetic/MultiplicationExpressionFactorty.h"

#include "expressions/action/arithmetic/MultiplicationExpression.h"

std::unique_ptr<BaseExpression> MultiplicationExpressionFactorty::generate(std::deque<std::unique_ptr<BaseExpression> > &arguments, std::shared_ptr<Scope> &scope) {

    return std::make_unique<MultiplicationExpression>(std::move(arguments[0]), std::move(arguments[1]));
}


int MultiplicationExpressionFactorty::paramSize() {
    return 2;
}

std::string MultiplicationExpressionFactorty::startToken() {
    return "*";
}

int MultiplicationExpressionFactorty::indexStart() {
    return -1;
}
