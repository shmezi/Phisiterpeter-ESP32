//
// Created by Ezra Golombek on 02/11/2025.
//

#include "../../include/expressions/action/PrintExpression.h"

#include <iostream>
#include <ostream>

#include "../../include/base/Scope.h"
#include "expressions/internal/VoidExpression.h"

std::shared_ptr<Expression> PrintExpression::interpret(std::shared_ptr<Scope> scope) {
    std::cout << this->expression->interpertAsString(scope) << std::endl;
    return std::make_unique<VoidExpression>();
}

PrintExpression::~PrintExpression() = default;

std::string PrintExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return expression->interpertAsString(scope);
}
