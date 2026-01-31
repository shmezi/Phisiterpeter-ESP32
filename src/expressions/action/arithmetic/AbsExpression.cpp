//
// Created by Ezra Golombek on 30/01/2026.
//

#include "../../../../include/expressions/action/arithmetic/AbsExpression.h"

#include "expressions/value/NumberExpression.h"

std::string AbsExpression::expressionName() {
    return "abs";
}

std::shared_ptr<Expression> AbsExpression::interpret(std::shared_ptr<Scope> scope) {
    return std::make_shared<NumberExpression>(
        std::abs(dynamic_cast<NumberExpression *>(number->interpret(scope).get())->contents));
}

std::string AbsExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}
