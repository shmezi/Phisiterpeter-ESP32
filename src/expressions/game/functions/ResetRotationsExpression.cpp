//
// Created by Ezra Golombek on 31/01/2026.
//

#include "../../../../include/expressions/game/functions/ResetRotationsExpression.h"

#include "expressions/game/objects/MotorExpression.h"
#include "expressions/internal/VoidExpression.h"


std::string ResetRotationsExpression::expressionName() {
    return "reset";
}

std::shared_ptr<Expression> ResetRotationsExpression::interpret(std::shared_ptr<Scope> scope) {
    dynamic_cast<MotorExpression *>(motor->interpret(scope).get())->rotations = 0;

    return std::make_shared<VoidExpression>();
}
