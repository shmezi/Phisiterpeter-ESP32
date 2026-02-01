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


    ScheduleLoop::getInstance()->runAfterPeriod(static_cast<int>(evaluatedDuration), [passedCodeblock = codeblock,s = scope] {
        passedCodeblock->interpret(s);
    });
    return std::make_shared<VoidExpression>();
}
