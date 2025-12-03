//
// Created by Ezra Golombek on 01/12/2025.
//

#ifndef PHISITERPETER_ESP32_WHENEXPRESSION_H
#define PHISITERPETER_ESP32_WHENEXPRESSION_H
#include "expressions/Expression.h"


class WhenExpression : public Expression {
    std::shared_ptr<Expression> condition;
    std::shared_ptr<Expression> codeblock;

public:
    std::string expressionName() override;

    std::unique_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    WhenExpression(std::unique_ptr<Expression> condition,
                   std::unique_ptr<Expression> codeblock) : condition(std::shared_ptr(std::move(condition))),
                                                            codeblock(std::shared_ptr(std::move(codeblock))) {
    }
};


#endif //PHISITERPETER_ESP32_WHENEXPRESSION_H
