//
// Created by Ezra Golombek on 24/11/2025.
//
#include <expressions/action/control/ClarificationBracketExpression.h>

#include "Utils.h"
#include "expressions/value/NumberExpression.h"

std::shared_ptr<Expression> ClarificationBracketExpression::interpret(std::shared_ptr<Scope> scope) {

    bool first = true;
    for (auto &expression: this->expressions) {
        if (first) {
            first = false;
            continue;
        }
        expression->interpret(scope);
    }


    return this->expressions.front()->interpret(scope);
}

std::string ClarificationBracketExpression::interpretAsString(std::shared_ptr<Scope> scope) {
    return this->expressions.front()->interpretAsString(scope);
}

int ClarificationBracketExpression::expressionCount() const {
    return static_cast<int>(this->expressions.size());
}
