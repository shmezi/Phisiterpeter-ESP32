//
// Created by Ezra Golombek on 06/12/2025.
//

#include "../../../../include/factories/game/objects/GyroScopeExpressionFactory.h"

#include <algorithm>

#include "expressions/action/control/ValueHoldExpression.h"
#include "../../../../include/expressions/game/objects/GyroScopeSensorExpression.h"
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

std::unique_ptr<BaseExpression> GyroScopeExpressionFactory::generate(std::deque<std::unique_ptr<BaseExpression> > &arguments,
                                                                 std::shared_ptr<Scope> &scope) {
    auto a = arguments[0]->interpret(scope);
    const auto toggle = dynamic_cast<BooleanExpression *>(std::move(a).get());

    return std::make_unique<ValueHoldExpression>(std::make_shared<GyroScopeSensorExpression>(toggle->contents) );
}
