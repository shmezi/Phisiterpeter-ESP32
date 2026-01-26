//
// Created by Ezra Golombek on 08/11/2025.
//

#ifndef PHISILANDINTERPRETER_ANDEXPRESSION_H
#define PHISILANDINTERPRETER_ANDEXPRESSION_H
#include "expressions/BaseExpression.h"


class AndExpression : public BaseExpression{
    std::unique_ptr<BaseExpression> right; std::unique_ptr<BaseExpression> left;
public:

    std::string expressionName() override;

     std::shared_ptr<BaseExpression>interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
    AndExpression(std::unique_ptr<BaseExpression> right, std::unique_ptr<BaseExpression> left);

};


#endif //PHISILANDINTERPRETER_ANDEXPRESSION_H