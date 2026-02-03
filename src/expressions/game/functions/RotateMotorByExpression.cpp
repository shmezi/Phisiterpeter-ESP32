//
// Created by Ezra Golombek on 31/01/2026.
//

#include "../../../../include/expressions/game/functions/RotateMotorByExpression.h"

#include <cmath>

#include "Utils.h"
#include "expressions/game/objects/MotorExpression.h"
#include "expressions/internal/VoidExpression.h"
#include "expressions/value/NumberExpression.h"

std::string RotateMotorByExpression::expressionName() {
    return "rotate";
}


std::shared_ptr<Expression> RotateMotorByExpression::interpret(std::shared_ptr<Scope> scope) {
    const auto evaluatedMotor = dynamic_cast<MotorExpression *>(motor->interpret(scope).get());
    auto evaluatedRotations = std::dynamic_pointer_cast<NumberExpression>(rotateTo->interpret(scope));
    auto evaluatedSpeed = std::dynamic_pointer_cast<NumberExpression>(speed->interpret(scope));


    evaluatedMotor->rotateUntilRotation(evaluatedRotations->contents, evaluatedSpeed->contents);
    return std::make_shared<VoidExpression>();
}
