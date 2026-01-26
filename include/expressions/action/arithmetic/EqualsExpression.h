//
// Created by Ezra Golombek on 30/11/2025.
//

#ifndef PHISILANDINTERPRETER_EQUALSEXPRESSION_H
#define PHISILANDINTERPRETER_EQUALSEXPRESSION_H
#include "expressions/BaseExpression.h"


class EqualsExpression : public BaseExpression {
    std::unique_ptr<BaseExpression> left;
    std::unique_ptr<BaseExpression> right;

public:
   std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string expressionName() override { return "Equals"; };

    EqualsExpression(std::unique_ptr<BaseExpression> right, std::unique_ptr<BaseExpression> left);

    ~EqualsExpression() override = default;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
};


#endif //PHISILANDINTERPRETER_EQUALSEXPRESSION_H