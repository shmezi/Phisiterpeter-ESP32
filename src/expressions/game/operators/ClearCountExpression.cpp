//
// Created by Ezra Golombek on 11/12/2025.
//

#include "../../../../include/expressions/game/operators/ClearCountExpression.h"

#include "../../../../include/expressions/game/objects/MotorExpression.h"
#include "expressions/internal/VoidExpression.h"

std::string ClearCountExpression::expressionName() {
    return "resetMotorRotationCount";
}

std::shared_ptr<Expression> ClearCountExpression::interpret(std::shared_ptr<Scope> scope) {
    auto castMotor = dynamic_cast<MotorExpression *>(motor->interpret(scope).get());
    castMotor->rotations = 0;
    return std::make_shared<VoidExpression>();
}

std::string ClearCountExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}

ClearCountExpression::ClearCountExpression(std::unique_ptr<Expression> motor) : motor(std::move(motor)) {
}
