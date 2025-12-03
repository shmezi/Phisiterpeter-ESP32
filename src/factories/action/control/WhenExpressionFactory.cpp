//
// Created by Ezra Golombek on 02/12/2025.
//

#include "../../../../include/factories/action/control/WhenExpressionFactory.h"

#include "../../../../include/expressions/action/control/WhenExpression.h"

std::string WhenExpressionFactory::startToken() {
    return "when";
}

int WhenExpressionFactory::indexStart() {
    return 0;
}

int WhenExpressionFactory::paramSize() {
    return 2;
}

std::unique_ptr<Expression> WhenExpressionFactory::generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                            std::shared_ptr<Scope> &scope) {
    return std::make_unique<WhenExpression>(std::move(arguments[0]), std::move(arguments[1]));
}
