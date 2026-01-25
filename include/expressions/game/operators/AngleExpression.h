//
// Created by Ezra Golombek on 07/12/2025.
//

#ifndef PHISITERPETER_ESP32_ANGLEEXPRESSION_H
#define PHISITERPETER_ESP32_ANGLEEXPRESSION_H
#include "expressions/Expression.h"


class AngleExpression : public Expression{
    std::unique_ptr<Expression> encoder;
public:
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
    AngleExpression(std::unique_ptr<Expression> encoder);
};


#endif //PHISITERPETER_ESP32_ANGLEEXPRESSION_H