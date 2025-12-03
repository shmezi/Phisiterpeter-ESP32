//
// Created by Ezra Golombek on 02/12/2025.
//

#include "../../../../include/factories/action/control/WhileExpressionFactory.h"

#include "expressions/action/control/WhileExpression.h"

int WhileExpressionFactory::indexStart() {
    return 0;
}

int WhileExpressionFactory::paramSize() {
    return 2;
}

std::string WhileExpressionFactory::startToken() {
    return "while";
}

std::unique_ptr<Expression> WhileExpressionFactory::generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                          std::shared_ptr<Scope> &scope) {
    return std::make_unique<WhileExpression>(std::move(arguments[0]), std::move(arguments[1]));
}