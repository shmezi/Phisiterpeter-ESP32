//
// Created by Ezra Golombek on 30/11/2025.
//

#ifndef PHISILANDINTERPRETER_DIVISIONEXPRESSION_H
#define PHISILANDINTERPRETER_DIVISIONEXPRESSION_H
#include "expressions/BaseExpression.h"


class DivisionExpression : public BaseExpression {
    std::unique_ptr<BaseExpression> left;
    std::unique_ptr<BaseExpression> right;

public:
    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string expressionName() override { return "Division"; };

    DivisionExpression(std::unique_ptr<BaseExpression> right, std::unique_ptr<BaseExpression> left);

    ~DivisionExpression() override = default;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
};

#endif //PHISILANDINTERPRETER_DIVISIONEXPRESSION_H
