//
// Created by Ezra Golombek on 05/11/2025.
//

#include "../../../../include/expressions/action/control/CodeblockExpression.h"

#include <iostream>
#include <ostream>

#include "../../../../include/base/Scope.h"
#include "Utils.h"
#include "../../../../include/expressions/action/control/ReturnExpression.h"
#include "expressions/internal/DummyExpression.h"
#include "expressions/internal/ReturnValue.h"
#include "expressions/internal/VoidExpression.h"
#include "expressions/value/NumberExpression.h"
#include "expressions/value/TextExpression.h"

std::string CodeblockExpression::expressionName() {
    return "codeblock";
}

std::string CodeblockExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "CODEBLOCK of scope: " + scope->scopeId + " With " + std::to_string(expressions.size()) + " expressions.";
}


std::shared_ptr<Expression> CodeblockExpression::interpret(std::shared_ptr<Scope> scope) {

    const auto funcScope = scope->scopeId == "headScope" ? std::make_shared<Scope>("generic", scope) : scope;

    for (const auto &expression: this->expressions) {
        auto evaluatedResult = expression->interpret(funcScope);

        if (evaluatedResult->expressionName() != "returnValue") {
            continue;
        }
        if (scope->scopeId == "headScope") {
            const auto returnedValue = dynamic_cast<ReturnValue *>(evaluatedResult.get());
            if (!returnedValue) {
                debug::error("Expected ReturnValue but got something else!");
                return std::make_unique<VoidExpression>();
            }
            return std::move(returnedValue->contents);
        }
        return (evaluatedResult);
    }
    return std::make_unique<VoidExpression>();
}
