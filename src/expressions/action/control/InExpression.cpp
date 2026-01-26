//
// Created by Ezra Golombek on 03/12/2025.
//

#include "factories/action/control/InExpression.h"

#include "expressions/internal/VoidExpression.h"

std::string InExpression::expressionName() {
    return "in";
}

std::shared_ptr<BaseExpression> InExpression::interpret(std::shared_ptr<Scope> scope) {
return std::make_unique<VoidExpression>();
}

std::string InExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "";
}
