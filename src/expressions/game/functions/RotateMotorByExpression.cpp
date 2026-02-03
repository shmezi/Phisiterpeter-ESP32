//
// Created by Ezra Golombek on 31/01/2026.
//

#include "../../../../include/expressions/game/functions/RotateMotorByExpression.h"

#include "expressions/game/objects/MotorExpression.h"
#include "expressions/internal/VoidExpression.h"

std::string RotateMotorByExpression::expressionName() {
    return "rotate";
}

std::shared_ptr<Expression> RotateMotorByExpression::interpret(std::shared_ptr<Scope> scope) {
    dynamic_cast<MotorExpression *>(motor->interpret(scope).get())->rotate();
    return std::make_shared<VoidExpression>();
}
