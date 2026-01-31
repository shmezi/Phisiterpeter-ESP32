//
// Created by Ezra Golombek on 31/01/2026.
//

#include "expressions/action/control/AfterExpression.h"

#include "base/ScheduleLoop.h"
#include "expressions/action/control/CodeblockExpression.h"
#include "expressions/internal/VoidExpression.h"
#include "expressions/value/NumberExpression.h"

std::string AfterExpression::expressionName() {
    return "after";
}

std::shared_ptr<Expression> AfterExpression::interpret(std::shared_ptr<Scope> scope) {
    const auto evaluatedDuration = dynamic_cast<NumberExpression *>(duration->interpret(scope).get())->contents;
    const auto evaluatedCodeblock = dynamic_cast<CodeblockExpression *>(codeblock->interpret(scope).get());

    ScheduleLoop::getInstance()->runAfterPeriod(static_cast<int>(evaluatedDuration), [evaluatedCodeblock,scope] {
        for (auto &expression: evaluatedCodeblock->expressions) {
            expression->interpret(scope);
        };
    });
    return std::make_shared<VoidExpression>();
}
