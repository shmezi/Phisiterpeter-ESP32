//
// Created by Ezra Golombek on 03/12/2025.
//


#include "../../../../include/expressions/action/control/RangeOperatorExpression.h"

std::string RangeOperatorExpression::expressionName() {
    return "range";
}

std::unique_ptr<Expression> RangeOperatorExpression::interpret(std::shared_ptr<Scope> scope) {
    return first->interpret(scope)->toOperator(second->interpret(scope), scope);
}

std::string RangeOperatorExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}

RangeOperatorExpression::RangeOperatorExpression(std::unique_ptr<Expression> start,
                                                 std::unique_ptr<Expression> end) : first(
        std::move(start)), second(std::move(end)) {
}
