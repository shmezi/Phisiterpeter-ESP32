//
// Created by Ezra Golombek on 11/12/2025.
//

#include "../../../../include/expressions/game/functions/OnEventExpression.h"

#include <algorithm>

#include "Utils.h"
#include "base/ScheduleLoop.h"
#include "base/Scope.h"
#include "expressions/action/control/ValueHoldExpression.h"
#include "expressions/internal/VoidExpression.h"
#include "expressions/value/NumberExpression.h"

std::string OnEventExpression::expressionName() {
    return "onEvent";
}

std::shared_ptr<BaseExpression> OnEventExpression::interpret(std::shared_ptr<Scope> scope) {
    const auto evaluatedEventId = eventId->interpertAsString(scope);



    ScheduleLoop::getInstance()->onEventListener(evaluatedEventId, [scope,evaluatedEventId, cb = codeBlock](int value) {

        auto newScope = std::make_shared<Scope>("on" + evaluatedEventId, scope);

        newScope->setVariable("value", std::make_shared<NumberExpression>(value));

        cb->interpret(newScope);
    });
    return std::make_shared<VoidExpression>();
}

std::string OnEventExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}

OnEventExpression::OnEventExpression(std::unique_ptr<BaseExpression> eventId, std::unique_ptr<BaseExpression> codeBlock)
    : eventId(std::shared_ptr(std::move(eventId))), codeBlock(std::shared_ptr(std::move(codeBlock))) {
}
