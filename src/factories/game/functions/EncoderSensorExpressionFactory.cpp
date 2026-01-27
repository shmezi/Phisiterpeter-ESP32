//
// Created by Ezra Golombek on 27/01/2026.
//

#include "../../../../include/factories/game/functions/EncoderSensorExpressionFactory.h"

#include "expressions/game/objects/EncoderSensorExpression.h"

std::string EncoderSensorExpressionFactory::startToken() {
    return "encoder";
}

int EncoderSensorExpressionFactory::indexStart() {
    return 0;
}

int EncoderSensorExpressionFactory::paramSize() {
    return 0;
}


std::unique_ptr<Expression> EncoderSensorExpressionFactory::generate(
    std::deque<std::unique_ptr<Expression> > &arguments,
    std::shared_ptr<Scope> &scope) {
    return std::make_unique<EncoderSensorExpression>();
}
