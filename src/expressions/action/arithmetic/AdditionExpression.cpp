//
// Created by Ezra Golombek on 30/10/2025.
//

#include "../../../../include/expressions/action/arithmetic/AdditionExpression.h"

#include <iostream>
#include <ostream>

#include "../../../../include/base/Scope.h"
#include "expressions/value/NumberExpression.h"


std::unique_ptr<Expression> AdditionExpression::interpret(std::shared_ptr<Scope> scope) {
    return (right->interpret(scope)->addition(left->interpret(scope),scope));
}

AdditionExpression::AdditionExpression(std::unique_ptr<Expression> right, std::unique_ptr<Expression> left) {
    this->left = std::move(left);
    this->right = std::move(right);
    //Most likely need to shift to something that allows for the pointers stay.. given that it could be a reference to a variable.
}

std::string AdditionExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}
