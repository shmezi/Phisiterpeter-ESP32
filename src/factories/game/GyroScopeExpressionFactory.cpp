//
// Created by Ezra Golombek on 06/12/2025.
//

#include "../../../include/factories/game/GyroScopeExpressionFactory.h"

#include <algorithm>

#include "expressions/action/control/ValueHoldExpression.h"
#include "../../../include/expressions/game/GyroScopeSensorExpression.h"
#include "expressions/value/BooleanExpression.h"

std::string GyroScopeExpressionFactory::startToken() {
    return "gyro";
}

int GyroScopeExpressionFactory::indexStart() {
    return 0;
}

int GyroScopeExpressionFactory::paramSize() {
    return 1;
}

std::unique_ptr<Expression> GyroScopeExpressionFactory::generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                                 std::shared_ptr<Scope> &scope) {
    auto a = arguments[0]->interpret(scope);
    const auto toggle = dynamic_cast<BooleanExpression *>(std::move(a).get());

    return std::make_unique<ValueHoldExpression>(std::make_shared<GyroScopeSensorExpression>(toggle->contents) );
}
