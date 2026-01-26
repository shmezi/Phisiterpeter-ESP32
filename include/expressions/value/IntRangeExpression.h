//
// Created by Ezra Golombek on 03/12/2025.
//

#ifndef PHISITERPETER_ESP32_INTRANGE_H
#define PHISITERPETER_ESP32_INTRANGE_H
#include "expressions/BaseExpression.h"


class IntRangeExpression : public BaseExpression {
    int startRange;
    int endRange;

public:
    std::string expressionName() override;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    IntRangeExpression(int startRange, int endRange);
};


#endif //PHISITERPETER_ESP32_INTRANGE_H
