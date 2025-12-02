//
// Created by Ezra Golombek on 01/12/2025.
//

#include "expressions/game/WhenExpression.h"

#include "expressions/internal/VoidExpression.h"

std::string WhenExpression::expressionName() {
    return "when";
}

std::unique_ptr<Expression> WhenExpression::interpret(std::shared_ptr<Scope> scope) {
return std::make_unique<VoidExpression>();
}

std::string WhenExpression::interpertAsString(std::shared_ptr<Scope> scope) {
return  "";
}


