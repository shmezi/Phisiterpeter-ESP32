//
// Created by Ezra Golombek on 30/11/2025.
//

#include "../../../../include/expressions/action/arithmetic/GreaterExpression.h"

#include <expressions/action/arithmetic/AdditionExpression.h>

std::shared_ptr<BaseExpression> GreaterExpression::interpret(std::shared_ptr<Scope> scope) {
    return (right->interpret(scope)->greater(left->interpret(scope),scope));
}

GreaterExpression::GreaterExpression(std::unique_ptr<BaseExpression> right, std::unique_ptr<BaseExpression> left) {
    this->left = std::move(left);
    this->right = std::move(right);
    //Most likely need to shift to something that allows for the pointers stay.. given that it could be a reference to a variable.
}

std::string GreaterExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}
