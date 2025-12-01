//
// Created by Ezra Golombek on 08/11/2025.
//


#include <string>

#include "expressions/action/bool/AndExpression.h"

#include <any>

class Scope;

std::string AndExpression::expressionName() {
    return "and";
}

std::unique_ptr<Expression> AndExpression::interpret(std::shared_ptr<Scope> scope) {
    return (left->interpret(scope)->andOperator(right->interpret(scope), scope));
}

std::string AndExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}

AndExpression::AndExpression(std::unique_ptr<Expression> right, std::unique_ptr<Expression> left) {
    this->left = std::move(left);
    this->right = std::move(right);
}
