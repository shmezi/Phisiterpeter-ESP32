//
// Created by Ezra Golombek on 06/11/2025.
//

#include "../../../include/expressions/internal/DynamicExpression.h"

#include "../../../include/base/Scope.h"
#include "Utils.h"
#include "expressions/internal/ReturnValue.h"

std::string DynamicExpression::expressionName() {
    return "dynamicExpression";
}

std::shared_ptr<Expression> DynamicExpression::interpret(std::shared_ptr<Scope> scope) {
    auto secondaryScope = std::make_shared<Scope>("functionCallScope", scope);
    for (auto &expression: arguments) {
        secondaryScope->setVariable(expression.name, (expression.argument->interpret(secondaryScope)));
    }
    const auto evaluated = codeblock->interpret(secondaryScope);
    if (evaluated->expressionName() == "returnValue")
        return std::move(dynamic_cast<ReturnValue *>(evaluated.get())->contents);
    return (evaluated->interpret(secondaryScope));
}

std::string DynamicExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}
