//
// Created by Ezra Golombek on 07/12/2025.
//

#include "expressions/action/control/ValueHoldExpression.h"

std::string ValueHoldExpression::expressionName() {
    return "Value-" + expression->expressionName();
}

std::shared_ptr<Expression> ValueHoldExpression::interpret(std::shared_ptr<Scope> scope) {
    return expression;
}

std::string ValueHoldExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}

ValueHoldExpression::ValueHoldExpression(const std::shared_ptr<Expression> &expression) : expression(expression) {
}
