//
// Created by Ezra Golombek on 03/02/2026.
//

#include "../../../../include/expressions/game/functions/DegreesExpression.h"

#include <cmath>

#include "expressions/game/objects/MotorExpression.h"
#include "expressions/value/NumberExpression.h"

std::string DegreesExpression::expressionName() {
    return "degrees";
}

double wrap360(const double angle) {
    double result = std::fmod(angle, 360.0);
    if (result < 0) result += 360.0;
    return result;
}

std::shared_ptr<Expression> DegreesExpression::interpret(std::shared_ptr<Scope> scope) {
    auto actualMotor = dynamic_cast<MotorExpression *>(motor->interpret(scope).get());

    return std::make_shared<NumberExpression>(wrap360(actualMotor->rotations * 1.092));
}
