//
// Created by Ezra Golombek on 30/11/2025.
//

#include "../../../../include/expressions/action/arithmetic/LesserExpression.h"

std::shared_ptr<Expression> LesserExpression::interpret(std::shared_ptr<Scope> scope) {
    return (right->interpret(scope)->lesser(left->interpret(scope), scope));
}

LesserExpression::LesserExpression(std::unique_ptr<Expression> right, std::unique_ptr<Expression> left) {
    this->left = std::move(left);
    this->right = std::move(right);
    //Most likely need to shift to something that allows for the pointers stay.. given that it could be a reference to a variable.
}

std::string LesserExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}
