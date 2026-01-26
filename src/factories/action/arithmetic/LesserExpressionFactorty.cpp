//
// Created by Ezra Golombek on 30/11/2025.
//

#include "../../../../include/factories/action/arithmetic/LesserExpressionFactorty.h"

#include "expressions/action/arithmetic/LesserExpression.h"

std::unique_ptr<BaseExpression> LesserExpressionFactorty::generate(std::deque<std::unique_ptr<BaseExpression> > &arguments, std::shared_ptr<Scope> &scope) {

    return std::make_unique<LesserExpression>(std::move(arguments[0]), std::move(arguments[1]));
}


int LesserExpressionFactorty::paramSize() {
    return 2;
}

std::string LesserExpressionFactorty::startToken() {
    return "<";
}

int LesserExpressionFactorty::indexStart() {
    return -1;
}
