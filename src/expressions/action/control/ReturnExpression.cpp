//
// Created by Ezra Golombek on 06/11/2025.
//

#include "../../../../include/expressions/action/control/ReturnExpression.h"

#include <string>

#include "expressions/internal/ReturnValue.h"

std::string ReturnExpression::expressionName() {
    return "returnStatement";
}

std::shared_ptr<BaseExpression> ReturnExpression::interpret(std::shared_ptr<Scope> scope) {
    return (std::make_shared<ReturnValue>(expression->interpret(scope)));
}


std::string ReturnExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "returnStatement";
}

std::string ReturnExpression::instanceId() {
    return "returnStatement";
}
