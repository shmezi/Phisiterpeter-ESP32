//
// Created by Ezra Golombek on 03/12/2025.
//

#include "../../../include/factories/game/MotorExpressionFactory.h"

#include "expressions/action/control/ValueHoldExpression.h"
#include "expressions/game/MotorExpression.h"

std::string MotorExpressionFactory::startToken() {
    return "motor";
}

int MotorExpressionFactory::indexStart() {
    return 0;
}

int MotorExpressionFactory::paramSize() {
    return 5;
}

std::unique_ptr<Expression> MotorExpressionFactory::generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                             std::shared_ptr<Scope> &scope) {
    return std::make_unique<ValueHoldExpression>(std::make_shared<MotorExpression>(std::move(arguments[0]),
            std::move(arguments[1]),
            std::move(arguments[2]),
            std::move(arguments[3]),
            std::move(arguments[4]))
    );
}
