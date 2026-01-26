//
// Created by Ezra Golombek on 07/12/2025.
//

#include "factories/action/list/ClearListExpressionFactory.h"

#include "expressions/action/list/ClearListExpression.h"

std::string ClearListExpressionFactory::startToken() {
    return "clear";
}

int ClearListExpressionFactory::indexStart() {
    return 0;
}

int ClearListExpressionFactory::paramSize() {
    return 1;
}

std::unique_ptr<BaseExpression> ClearListExpressionFactory::generate(std::deque<std::unique_ptr<BaseExpression> > &arguments,
                                                                 std::shared_ptr<Scope> &scope) {
    return std::make_unique<ClearListExpression>(std::move(arguments[0]));
}
