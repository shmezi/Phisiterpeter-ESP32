//
// Created by Ezra Golombek on 29/11/2025.
//

#ifndef PHISILANDINTERPRETER_RETURNVALUE_H
#define PHISILANDINTERPRETER_RETURNVALUE_H
#include "expressions/BaseExpression.h"


class ReturnValue : public BaseExpression {
public:
    std::shared_ptr<BaseExpression> contents;

    std::string expressionName() override;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    explicit ReturnValue(std::shared_ptr<BaseExpression> contents) : contents(std::move(contents)) {
    }
};


#endif //PHISILANDINTERPRETER_RETURNVALUE_H
