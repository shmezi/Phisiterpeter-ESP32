//
// Created by Ezra Golombek on 02/11/2025.
//

#include "../../include/expressions/action/PrintExpression.h"

#include <iostream>
#include <ostream>

#include "../../include/base/Scope.h"
#include "expressions/internal/VoidExpression.h"

ExpressionInfo PrintExpression::getInfo() {
    return {
        0,
        "print",
        {
            {"value", "any"}
        }
    };
}


std::shared_ptr<BaseExpression> PrintExpression::interpret(std::shared_ptr<Scope> scope) {
    std::cout << this->expression->interpertAsString(scope) << std::endl;
    return std::make_unique<VoidExpression>();
}

PrintExpression::~PrintExpression() = default;

std::string PrintExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return expression->interpertAsString(scope);
}


std::unique_ptr<BaseExpression>
PrintExpression::generate(
    std::deque<std::unique_ptr<BaseExpression> > &arguments,
    std::shared_ptr<Scope> &scope
) {
    return std::make_unique<PrintExpression>(std::move(arguments[0]));
}
