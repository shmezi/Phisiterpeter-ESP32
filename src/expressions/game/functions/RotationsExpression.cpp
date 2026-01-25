//
// Created by Ezra Golombek on 07/12/2025.
//

#include "../../../../include/expressions/game/operators/RotationsExpression.h"

#include <algorithm>

#include "../../../../include/expressions/game/objects/MotorExpression.h"
#include "expressions/value/NumberExpression.h"

std::string RotationsExpression::expressionName() {
    return "rotations";
}

std::shared_ptr<Expression> RotationsExpression::interpret(std::shared_ptr<Scope> scope) {
    auto actualMotor = dynamic_cast<MotorExpression *>(motor->interpret(scope).get());

    return std::make_shared<NumberExpression>(actualMotor->rotations);
}

std::string RotationsExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}

RotationsExpression::RotationsExpression(std::unique_ptr<Expression> motor) : motor(std::move(motor)) {
}
