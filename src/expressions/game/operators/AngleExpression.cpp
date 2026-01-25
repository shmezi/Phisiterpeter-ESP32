//
// Created by Ezra Golombek on 07/12/2025.
//


#include "../../../../include/expressions/game/operators/AngleExpression.h"

#include <algorithm>

#include "../../../../include/expressions/game/objects/GyroScopeSensorExpression.h"
#include "expressions/value/NumberExpression.h"

std::string AngleExpression::expressionName() {
    return "angle";
}

std::shared_ptr<Expression> AngleExpression::interpret(std::shared_ptr<Scope> scope) {
    auto sensor = dynamic_cast<GyroScopeSensorExpression *>(encoder->interpret(scope).get());
    return std::make_shared<NumberExpression>(sensor->pitch());
}

std::string AngleExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}

AngleExpression::AngleExpression(std::unique_ptr<Expression> encoder) : encoder(std::move(encoder)) {
}
