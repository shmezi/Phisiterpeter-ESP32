//
// Created by Ezra Golombek on 11/12/2025.
//

#ifndef PHISITERPETER_ESP32_CLEARCOUNTEXPRESSION_H
#define PHISITERPETER_ESP32_CLEARCOUNTEXPRESSION_H
#include "expressions/Expression.h"


class ClearCountExpression : public Expression{
    std::unique_ptr<Expression> motor;
public:
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
    explicit ClearCountExpression (std::unique_ptr<Expression> motor);
};


#endif //PHISITERPETER_ESP32_CLEARCOUNTEXPRESSION_H