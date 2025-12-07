//
// Created by Ezra Golombek on 07/12/2025.
//

#include "ListExpressionFactory.h"

#include <algorithm>

#include "expressions/value/ListExpression.h"

std::string ListExpressionFactory::startToken() {
    return "[";
}

std::string ListExpressionFactory::endToken() {
    return "]";
}

int ListExpressionFactory::indexStart() {
    return 0;
}

int ListExpressionFactory::paramSize() {
    return 0;
}

std::unique_ptr<Expression> ListExpressionFactory::generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                            std::shared_ptr<Scope> &scope) {
    return std::make_unique<ListExpression>(std::move(arguments));
}
