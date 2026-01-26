//
// Created by Ezra Golombek on 11/11/2025.
//

#ifndef PHISILANDINTERPRETER_NOTEXPRESSION_H
#define PHISILANDINTERPRETER_NOTEXPRESSION_H
#include "expressions/BaseExpression.h"


class NotExpression : public BaseExpression {
    std::unique_ptr<BaseExpression> contents;

public:
    std::string expressionName() override;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    explicit NotExpression(std::unique_ptr<BaseExpression> expression) : contents(std::move(expression)) {
    }
};


#endif //PHISILANDINTERPRETER_NOTEXPRESSION_H
