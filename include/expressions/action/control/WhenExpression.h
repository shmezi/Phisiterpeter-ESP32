//
// Created by Ezra Golombek on 01/12/2025.
//

#ifndef PHISITERPETER_ESP32_WHENEXPRESSION_H
#define PHISITERPETER_ESP32_WHENEXPRESSION_H
#include "expressions/BaseExpression.h"


class WhenExpression : public BaseExpression {
    std::shared_ptr<BaseExpression> condition;
    std::shared_ptr<BaseExpression> codeblock;

public:
    std::string expressionName() override;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    WhenExpression(std::unique_ptr<BaseExpression> condition,
                   std::unique_ptr<BaseExpression> codeblock) : condition(std::shared_ptr(std::move(condition))),
                                                            codeblock(std::shared_ptr(std::move(codeblock))) {
    }
};


#endif //PHISITERPETER_ESP32_WHENEXPRESSION_H
