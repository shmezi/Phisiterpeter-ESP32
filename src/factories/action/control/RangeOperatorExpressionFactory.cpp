//
// Created by Ezra Golombek on 03/12/2025.
//


#include "factories/action/control/RangeOperatorExpressionFactory.h"

#include "../../../../include/expressions/action/control/RangeOperatorExpression.h"

std::string RangeOperatorExpressionFactory::startToken() {
    return "to";
}

int RangeOperatorExpressionFactory::indexStart() {
    return -1;
}

int RangeOperatorExpressionFactory::paramSize() {
    return 2;
}

std::unique_ptr<BaseExpression> RangeOperatorExpressionFactory::generate(
    std::deque<std::unique_ptr<BaseExpression> > &arguments,
    std::shared_ptr<Scope> &scope) {
    return std::make_unique<RangeOperatorExpression>(std::move(arguments[0]), std::move(arguments[1]));
}
