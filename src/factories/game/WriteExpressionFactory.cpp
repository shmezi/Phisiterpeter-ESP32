//
// Created by Ezra Golombek on 04/12/2025.
//

#include "../../../include/factories/game/functions/WriteExpressionFactory.h"

#include "../../../include/expressions/game/functions/WriteExpression.h"

std::string WriteExpressionFactory::startToken() {
    return "write";
}

int WriteExpressionFactory::indexStart() {
    return 0;
}

int WriteExpressionFactory::paramSize() {
    return 1;
}

std::unique_ptr<Expression> WriteExpressionFactory::generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                             std::shared_ptr<Scope> &scope) {
    return std::make_unique<WriteExpression>(std::move(arguments[0]), std::move(arguments[1]));
}
