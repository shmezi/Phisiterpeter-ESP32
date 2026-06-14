//
// Created by Ezra Golombek on 14/06/2026.
//

#include "../../../../include/expressions/action/arithmetic/MappingExpression.h"
#include "path/to/MappingExpression.h"
#include "expressions/value/NumberExpression.h"
#include "base/Scope.h"

MappingExpression::MappingExpression(
    std::unique_ptr<Expression> value,
    std::unique_ptr<Expression> inputMin,
    std::unique_ptr<Expression> inputMax,
    std::unique_ptr<Expression> outputMin,
    std::unique_ptr<Expression> outputMax)
{
    this->value     = std::move(value);
    this->inputMin  = std::move(inputMin);
    this->inputMax  = std::move(inputMax);
    this->outputMin = std::move(outputMin);
    this->outputMax = std::move(outputMax);
}

std::shared_ptr<Expression> MappingExpression::interpret(std::shared_ptr<Scope> scope) {
    // Interpret all child expressions to get their numeric values
    double val    = value->interpret(scope)->toNumber(scope);
    double inMin  = inputMin->interpret(scope)->toNumber(scope);
    double inMax  = inputMax->interpret(scope)->toNumber(scope);
    double outMin = outputMin->interpret(scope)->toNumber(scope);
    double outMax = outputMax->interpret(scope)->toNumber(scope);

    // Linear map: outMin + (val - inMin) * (outMax - outMin) / (inMax - inMin)
    double mapped = outMin + (val - inMin) * (outMax - outMin) / (inMax - inMin);

    return std::make_shared<NumberExpression>(mapped);
}

std::string MappingExpression::interpretAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpretAsString(scope);
}