//
// Created by Ezra Golombek on 31/01/2026.
//

#include "../../../../include/expressions/game/functions/RotateMotorByExpression.h"

#include "expressions/game/objects/MotorExpression.h"
#include "expressions/internal/VoidExpression.h"
#include "expressions/value/NumberExpression.h"

std::string RotateMotorByExpression::expressionName() {
    return "rotate";
}

RotateMotorByExpression::RotateMotorByExpression(std::unique_ptr<Expression> motor,
                                                 std::unique_ptr<Expression> rotateTo,
                                                 std::unique_ptr<Expression> speed) {
    this->motor = std::move(motor);
    this->rotateTo = std::move(rotateTo);
    this->speed = std::move(speed);
}

std::shared_ptr<Expression> RotateMotorByExpression::interpret(std::shared_ptr<Scope> scope) {
    const auto evaluatedMotor = dynamic_cast<MotorExpression *>(motor->interpret(scope).get());

    const auto evaluatedSpeed = dynamic_cast<NumberExpression *>(speed->interpret(scope).get());

    const auto evaluatedRotations = dynamic_cast<NumberExpression *>(rotateTo->interpret(scope).get());


    evaluatedMotor->rotateUntilRotation(evaluatedRotations->contents, evaluatedSpeed->contents);
    return std::make_shared<VoidExpression>();
}
