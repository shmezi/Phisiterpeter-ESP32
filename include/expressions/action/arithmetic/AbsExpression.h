//
// Created by Ezra Golombek on 30/01/2026.
//

#ifndef PHISITERPETER_ESP32_ABSEXPRESSION_H
#define PHISITERPETER_ESP32_ABSEXPRESSION_H
#include "expressions/Expression.h"


class AbsExpression : public Expression {
    std::unique_ptr<Expression> number;

public:
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    explicit AbsExpression(std::unique_ptr<Expression> number) : number(std::move(number)) {
    }
};


#endif //PHISITERPETER_ESP32_ABSEXPRESSION_H
