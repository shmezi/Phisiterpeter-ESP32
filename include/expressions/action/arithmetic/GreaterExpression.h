//
// Created by Ezra Golombek on 30/11/2025.
//

#ifndef PHISILANDINTERPRETER_GREATEREXPRESSION_H
#define PHISILANDINTERPRETER_GREATEREXPRESSION_H
#include "expressions/BaseExpression.h"


class GreaterExpression : public BaseExpression {
    std::unique_ptr<BaseExpression> left;
    std::unique_ptr<BaseExpression> right;

public:
  std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string expressionName() override { return "Greater"; };

    GreaterExpression(std::unique_ptr<BaseExpression> right, std::unique_ptr<BaseExpression> left);

    ~GreaterExpression() override = default;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
};


#endif //PHISILANDINTERPRETER_GREATEREXPRESSION_H