//
// Created by Ezra Golombek on 03/02/2026.
//

#include "../../../../include/expressions/game/functions/Wrap360Expression.h"

#include "Utils.h"
#include "expressions/value/NumberExpression.h"

std::string Wrap360Expression::expressionName() {
    return "wrap360";
}
#include <cmath>


double reverseAngle(double angle) {
    double normalized = fmod(angle, 360.0);
    if (normalized < 0) normalized += 360.0;

    double reversed = 360.0 - normalized;

    // Final wrap to ensure 360 becomes 0
    return fmod(reversed, 360.0);
}

std::shared_ptr<Expression> Wrap360Expression::interpret(std::shared_ptr<Scope> scope) {
    const auto evaluatedInputNumber = std::dynamic_pointer_cast<NumberExpression>(inputNumber->interpret(scope));
    return std::make_shared<NumberExpression>(debug::wrap360(reverseAngle( evaluatedInputNumber->contents)));
}
