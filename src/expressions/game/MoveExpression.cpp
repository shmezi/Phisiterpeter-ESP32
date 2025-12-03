//
// Created by Ezra Golombek on 03/12/2025.
//

#include "../../../include/expressions/action/control/MoveExpression.h"

#include "Utils.h"
#include "expressions/game/MotorExpression.h"
#include "expressions/internal/VoidExpression.h"
#include "expressions/value/BooleanExpression.h"

std::string MoveExpression::expressionName() {
    return "motor";
}

std::unique_ptr<Expression> MoveExpression::interpret(std::shared_ptr<Scope> scope) {
    const auto motorExpression = motor->interpret(scope);
    auto castMotor = dynamic_cast<MotorExpression *>(motorExpression.get());
    castMotor->move(dynamic_cast<BooleanExpression *>(direction->interpret(scope).get())->contents);

    return std::make_unique<VoidExpression>();
}

std::string MoveExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "motor spin woooooo";
}

MoveExpression::MoveExpression(std::unique_ptr<Expression> motor,
                               std::unique_ptr<Expression> direction) : motor(std::move(motor)),
                                                                        direction(std::move(direction)) {
}
