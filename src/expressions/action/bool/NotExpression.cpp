//
// Created by Ezra Golombek on 11/11/2025.
//


#include <any>
#include <string>
#include "expressions/action/bool/NotExpression.h"

class Scope;

std::string NotExpression::expressionName() {
    return "notExpression";
}

std::unique_ptr<Expression> NotExpression::interpret(std::shared_ptr<Scope> scope) {
    return (contents->interpret(scope)->notOperator(scope));
}

std::string NotExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}
