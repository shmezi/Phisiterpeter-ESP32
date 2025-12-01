//
// Created by Ezra Golombek on 30/11/2025.
//

#include "../../../../include/factories/action/arithmetic/UnEqualExpressionFactorty.h"

#include "expressions/action/arithmetic/UnEqualExpression.h"

std::unique_ptr<Expression> UnEqualExpressionFactorty::generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                                std::shared_ptr<Scope> &scope) {
    return std::make_unique<UnEqualExpression>(std::move(arguments[0]), std::move(arguments[1]));
}


int UnEqualExpressionFactorty::paramSize() {
    return 2;
}

std::string UnEqualExpressionFactorty::startToken() {
    return "!=";
}

int UnEqualExpressionFactorty::indexStart() {
    return -1;
}
