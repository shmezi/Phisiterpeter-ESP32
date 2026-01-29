#include "expressions/action/control/OnceExpression.h"

#include <algorithm>

#include "base/ScheduleLoop.h"
#include "expressions/internal/VoidExpression.h"
#include "expressions/value/BooleanExpression.h"
//
// Created by Ezra Golombek on 29/01/2026.
//
std::string OnceExpression::expressionName() {
    return "once";
}

std::shared_ptr<Expression> OnceExpression::interpret(std::shared_ptr<Scope> scope) {
    if (hasBeenInterpreted) return std::make_shared<VoidExpression>();
    hasBeenInterpreted = true;
    ScheduleLoop::getInstance()->addTask(
        [condition_sp = condition,hasRun_sp = &hasRun, scope, cb = codeblock] {
            const auto condition = dynamic_cast<BooleanExpression *>(condition_sp->interpret(scope).get())->contents;
            if (!condition && hasRun_sp) {
                *hasRun_sp = false;
                return;
            }
            if (hasRun_sp) return;
            cb->interpret(scope);
            *hasRun_sp = true;
        }

    );
    return std::make_unique<VoidExpression>();
}

std::string OnceExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "onceExpression";
}
