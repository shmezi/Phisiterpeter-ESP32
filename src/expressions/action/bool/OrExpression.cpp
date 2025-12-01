//
// Created by Ezra Golombek on 08/11/2025.
//

#include "expressions/action/bool/OrExpression.h"

#include <deque>
#include <string>

std::string OrExpression::expressionName() {
    return "or";
}

std::unique_ptr<Expression> OrExpression::interpret(std::shared_ptr<Scope> scope) {
    return (left->interpret(scope)->orOperator(right->interpret(scope), scope));
}

std::string OrExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}

OrExpression::OrExpression(std::unique_ptr<Expression> right, std::unique_ptr<Expression> left) {
    this->left = std::move(left);
    this->right = std::move(right);
}
