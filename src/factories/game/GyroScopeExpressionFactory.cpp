//
// Created by Ezra Golombek on 06/12/2025.
//

#include "../../../include/factories/game/GyroScopeExpressionFactory.h"

#include "expressions/game/GyroScopeSensorExpression.h"

std::string GyroScopeExpressionFactory::startToken() {
    return "gyro";
}

int GyroScopeExpressionFactory::indexStart() {
    return 0;
}

int GyroScopeExpressionFactory::paramSize() {
    return 0;
}

std::unique_ptr<Expression> GyroScopeExpressionFactory::generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                                 std::shared_ptr<Scope> &scope) {
    return std::make_unique<GyroScopeSensorExpression>();
}
