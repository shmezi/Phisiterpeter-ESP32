//
// Created by Ezra Golombek on 30/10/2025.
//

#ifndef PHISILANDINTERPRETER_ADDITIONEXPRESSION_H
#define PHISILANDINTERPRETER_ADDITIONEXPRESSION_H
#include <string>

#include "../../BaseExpression.h"


class AdditionExpression : public BaseExpression {
    std::unique_ptr<BaseExpression> left;
    std::unique_ptr<BaseExpression> right;

public:
    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string expressionName() override {return "Addition";};
    AdditionExpression(std::unique_ptr<BaseExpression> right, std::unique_ptr<BaseExpression> left);

    ~AdditionExpression() override = default;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
};


#endif //PHISILANDINTERPRETER_ADDITIONEXPRESSION_H
