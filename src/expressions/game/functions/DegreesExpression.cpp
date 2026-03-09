//
// Created by Ezra Golombek on 03/02/2026.
//

#include "../../../../include/expressions/game/functions/DegreesExpression.h"

#include <cmath>

#include "Utils.h"
#include "expressions/game/objects/MotorExpression.h"
#include "expressions/value/NumberExpression.h"

std::string DegreesExpression::expressionName() {
    return "degrees";
}


std::shared_ptr<Expression> DegreesExpression::interpret(std::shared_ptr<Scope> scope) {
    auto actualMotor = dynamic_cast<MotorExpression *>(motor->interpret(scope).get());

    return std::make_shared<NumberExpression>(debug::wrap360(actualMotor->rotations * 1.092));
}
