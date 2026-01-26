//
// Created by Ezra Golombek on 03/12/2025.
//

#ifndef PHISITERPETER_ESP32_RANGEEXPRESSION_H
#define PHISITERPETER_ESP32_RANGEEXPRESSION_H
#include "expressions/BaseExpression.h"


class RangeOperatorExpression : public BaseExpression {
    std::unique_ptr<BaseExpression> first;
    std::unique_ptr<BaseExpression> second;

public:
    std::string expressionName() override;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    RangeOperatorExpression(std::unique_ptr<BaseExpression> first, std::unique_ptr<BaseExpression> second);

};


#endif //PHISITERPETER_ESP32_RANGEEXPRESSION_H
