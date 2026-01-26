//
// Created by Ezra Golombek on 07/12/2025.
//

#include "factories/action/list/AddToListExpressionFactory.h"

#include "expressions/action/list/AddToListExpression.h"

std::string AddToListExpressionFactory::startToken() {
    return "add";
}

int AddToListExpressionFactory::indexStart() {
    return -1;
}

int AddToListExpressionFactory::paramSize() {
    return 2;
}

std::unique_ptr<BaseExpression> AddToListExpressionFactory::generate(std::deque<std::unique_ptr<BaseExpression> > &arguments,
                                                                 std::shared_ptr<Scope> &scope) {
    return std::make_unique<AddToListExpression>(std::move(arguments[0]),std::move(arguments[1]));
}
