//
// Created by Ezra Golombek on 01/12/2025.
//

#include "../../../../include/expressions/action/control/WhenExpression.h"

#include "Utils.h"
#include "base/Interpreter.h"
#include "base/ScheduleLoop.h"
#include "expressions/action/PrintExpression.h"
#include "expressions/game/StatusLEDExpression.h"
#include "expressions/internal/VoidExpression.h"
#include "expressions/value/BooleanExpression.h"
#include "expressions/value/NumberExpression.h"

std::string WhenExpression::expressionName() {
    return "when";
}


static auto a = StatusLEDExpression(make_unique<NumberExpression>(0), make_unique<NumberExpression>(250),
                                    make_unique<NumberExpression>(0));

std::unique_ptr<Expression> WhenExpression::interpret(std::shared_ptr<Scope> scope) {
    ScheduleLoop::getInstance()->addConditionalTask(
        [condition_sp = condition, scope] {
            return dynamic_cast<BooleanExpression *>(condition_sp->interpret(scope).get())->contents;
        }, [codeblock_sp = codeblock, scope] {
            codeblock_sp->interpret(scope);
        }

    );
    return std::make_unique<VoidExpression>();
}

std::string WhenExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "";
}
