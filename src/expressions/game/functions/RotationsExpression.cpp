//
// Created by Ezra Golombek on 07/12/2025.
//

#include "../../../../include/expressions/game/operators/RotationsExpression.h"

#include <algorithm>

#include "../../../../include/expressions/game/objects/MotorExpression.h"
#include "expressions/value/NumberExpression.h"
#include <cmath>

std::string RotationsExpression::expressionName() {
    return "rotations";
}


std::shared_ptr<Expression> RotationsExpression::interpret(std::shared_ptr<Scope> scope) {
    auto actualMotor = dynamic_cast<MotorExpression *>(motor->interpret(scope).get());
    //Encoder reads 11 times per rotation, gear ratio is 33. We want the rotations to return to us a degree
    // Thus to get purely rotations we should do: 11 * 33 = 330. However we want the degrees so we do 330 / 360 = 1.092.
    // Or do we? wrappedAngle = (angle % 360 + 360) % 360;
    //TODO REVERT AND MAKE A NEW EXPRESSION!
    //

    return std::make_shared<NumberExpression>(actualMotor->rotations / 330);
}

std::string RotationsExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}

RotationsExpression::RotationsExpression(std::unique_ptr<Expression> motor) : motor(std::move(motor)) {
}
