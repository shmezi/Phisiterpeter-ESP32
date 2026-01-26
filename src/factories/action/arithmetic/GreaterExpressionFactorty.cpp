//
// Created by Ezra Golombek on 30/11/2025.
//

#include "../../../../include/factories/action/arithmetic/GreaterExpressionFactorty.h"

#include "expressions/action/arithmetic/GreaterExpression.h"

std::unique_ptr<BaseExpression> GreaterExpressionFactorty::generate(std::deque<std::unique_ptr<BaseExpression> > &arguments, std::shared_ptr<Scope> &scope) {

    return std::make_unique<GreaterExpression>(std::move(arguments[0]), std::move(arguments[1]));
}


int GreaterExpressionFactorty::paramSize() {
    return 2;
}

std::string GreaterExpressionFactorty::startToken() {
    return ">";
}

int GreaterExpressionFactorty::indexStart() {
    return -1;
}
