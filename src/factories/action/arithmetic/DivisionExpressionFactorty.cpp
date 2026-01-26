//
// Created by Ezra Golombek on 30/11/2025.
//

#include "../../../../include/factories/action/arithmetic/DivisionExpressionFactorty.h"

#include "expressions/action/arithmetic/DivisionExpression.h"

std::unique_ptr<BaseExpression> DivisionExpressionFactorty::generate(std::deque<std::unique_ptr<BaseExpression> > &arguments, std::shared_ptr<Scope> &scope) {

    return std::make_unique<DivisionExpression>(std::move(arguments[0]), std::move(arguments[1]));
}


int DivisionExpressionFactorty::paramSize() {
    return 2;
}

std::string DivisionExpressionFactorty::startToken() {
    return "/";
}

int DivisionExpressionFactorty::indexStart() {
    return -1;
}
