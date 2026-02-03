//
// Created by Ezra Golombek on 03/02/2026.
//

#include "../../../../include/factories/game/functions/RotateMotorByExpressionFactory.h"

#include "expressions/game/functions/RotateMotorByExpression.h"

std::string RotateMotorByExpressionFactory::startToken() {
    return "rotate";
}

int RotateMotorByExpressionFactory::indexStart() {
    return 0;
}

int RotateMotorByExpressionFactory::paramSize() {
    return 3;
}

std::unique_ptr<Expression> RotateMotorByExpressionFactory::generate(std::deque<std::unique_ptr<Expression>> &arguments,
    std::shared_ptr<Scope> &scope) {
    return std::make_unique<RotateMotorByExpression>(std::move(arguments[0]),std::move(arguments[1]),std::move(arguments[2]));
}
