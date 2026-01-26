//
// Created by Ezra Golombek on 03/12/2025.
//


#include "expressions/value/IntRangeExpression.h"

std::string IntRangeExpression::expressionName() {
    return "IntRange";
}

std::shared_ptr<BaseExpression> IntRangeExpression::interpret(std::shared_ptr<Scope> scope) {
    return std::make_unique<IntRangeExpression>(startRange, endRange);
}

std::string IntRangeExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return std::to_string(startRange) + ".." + std::to_string(endRange);
}

IntRangeExpression::IntRangeExpression(int startRange,
                                       int endRange) : startRange(std::move(startRange)),
                                                       endRange(std::move(endRange)) {
}
