//
// Created by Ezra Golombek on 01/12/2025.
//

#ifndef PHISITERPETER_ESP32_WHENEXPRESSION_H
#define PHISITERPETER_ESP32_WHENEXPRESSION_H
#include "expressions/Expression.h"


class WhenExpression : public Expression{

public:

    std::string expressionName() override;

    std::unique_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
};


#endif //PHISITERPETER_ESP32_WHENEXPRESSION_H