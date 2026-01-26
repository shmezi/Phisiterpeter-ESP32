//
// Created by Ezra Golombek on 06/11/2025.
//

#ifndef PHISILANDINTERPRETER_DYNAMICEXPRESSION_H
#define PHISILANDINTERPRETER_DYNAMICEXPRESSION_H
#include <iostream>

#include "../BaseExpression.h"

#include <utility>

#include "../../base/PassedArgument.h"
#include "../action/control/CodeblockExpression.h"


class DynamicExpression : public BaseExpression {
    std::deque<PassedArgument> arguments;
    std::unique_ptr<CodeblockExpression>& codeblock; //Passed a reference from the factory.

public:
    std::string expressionName() override;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    DynamicExpression(
        std::deque<PassedArgument> arguments,
        std::unique_ptr<CodeblockExpression>&
        expression) : arguments(std::move(arguments)),codeblock(expression) {
    }
};


#endif //PHISILANDINTERPRETER_DYNAMICEXPRESSION_H
