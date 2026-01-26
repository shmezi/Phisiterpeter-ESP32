//
// Created by Ezra Golombek on 29/11/2025.
//

#include "../../../include/expressions/internal/ReturnValue.h"

#include <locale>

std::string ReturnValue::expressionName() {
    return "returnValue";
}

std::shared_ptr<BaseExpression> ReturnValue::interpret(std::shared_ptr<Scope> scope) {
    return std::make_shared<ReturnValue>(std::move(contents));
}

std::string ReturnValue::interpertAsString(std::shared_ptr<Scope> scope) {
    return (contents->interpertAsString(scope));
}
