//
// Created by Ezra Golombek on 03/12/2025.
//

#ifndef PHISITERPETER_ESP32_ITERATORTOEXPRESSION_H
#define PHISITERPETER_ESP32_ITERATORTOEXPRESSION_H
#include "expressions/BaseExpression.h"


class InExpression : BaseExpression {

public:
    std::string expressionName() override;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
};


#endif //PHISITERPETER_ESP32_ITERATORTOEXPRESSION_H