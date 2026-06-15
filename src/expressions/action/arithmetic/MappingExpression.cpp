//
// Created by Ezra Golombek on 14/06/2026.
//

#include "../../../../include/expressions/action/arithmetic/MappingExpression.h"
#include "expressions/value/NumberExpression.h"
#include "base/Scope.h"

MappingExpression::MappingExpression(
    std::unique_ptr<Expression> value,
    std::unique_ptr<Expression> inputMin,
    std::unique_ptr<Expression> inputMax,
    std::unique_ptr<Expression> outputMin,
    std::unique_ptr<Expression> outputMax) {
    this->value = std::move(value);
    this->inputMin = std::move(inputMin);
    this->inputMax = std::move(inputMax);
    this->outputMin = std::move(outputMin);
    this->outputMax = std::move(outputMax);
}

std::shared_ptr<Expression> MappingExpression::interpret(std::shared_ptr<Scope> scope) {
    float val = dynamic_cast<NumberExpression *>(value->interpret(scope).get())->contents;
    float inMin = dynamic_cast<NumberExpression *>(inputMin->interpret(scope).get())->contents;
    float inMax = dynamic_cast<NumberExpression *>(inputMax->interpret(scope).get())->contents;
    float outMin = dynamic_cast<NumberExpression *>(outputMin->interpret(scope).get())->contents;
    float outMax = dynamic_cast<NumberExpression *>(outputMax->interpret(scope).get())->contents;

    // Arduino formula but in float — no integer truncation
    float mapped = (val - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;

    // Clamp to output range (handles reversed ranges too)
    float lo = std::min(outMin, outMax);
    float hi = std::max(outMin, outMax);
    mapped = std::clamp(mapped, lo, hi);

    return std::make_shared<NumberExpression>(mapped);
}

std::string MappingExpression::interpretAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpretAsString(scope);
}

std::string MappingExpression::expressionName() {
    return "mapping";
}
