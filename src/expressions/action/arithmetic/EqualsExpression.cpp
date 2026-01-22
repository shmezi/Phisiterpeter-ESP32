//
// Created by Ezra Golombek on 30/11/2025.
//

#include "../../../../include/expressions/action/arithmetic/EqualsExpression.h"

std::shared_ptr<Expression> EqualsExpression::interpret(std::shared_ptr<Scope> scope) {
    return (right->interpret(scope)->equal(left->interpret(scope), scope));
}

EqualsExpression::EqualsExpression(std::unique_ptr<Expression> right, std::unique_ptr<Expression> left) {
    this->left = std::move(left);
    this->right = std::move(right);
    //Most likely need to shift to something that allows for the pointers stay.. given that it could be a reference to a variable.
}

std::string EqualsExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}
