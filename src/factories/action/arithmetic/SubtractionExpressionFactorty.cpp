//
// Created by Ezra Golombek on 30/11/2025.
//

#include "../../../../include/factories/action/arithmetic/SubtractionExpressionFactorty.h"

#include "expressions/action/arithmetic/SubtractionExpression.h"

std::unique_ptr<Expression> SubtractionExpressionFactorty::generate(std::deque<std::unique_ptr<Expression> > &arguments, std::shared_ptr<Scope> &scope) {

    return std::make_unique<SubtractionExpression>(std::move(arguments[0]), std::move(arguments[1]));
}


int SubtractionExpressionFactorty::paramSize() {
    return 2;
}

std::string SubtractionExpressionFactorty::startToken() {
    return "-";
}

int SubtractionExpressionFactorty::indexStart() {
    return -1;
}
