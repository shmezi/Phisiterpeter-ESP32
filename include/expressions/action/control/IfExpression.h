//
// Created by Ezra Golombek on 08/11/2025.
//

#ifndef PHISILANDINTERPRETER_IFEXPRESSION_H
#define PHISILANDINTERPRETER_IFEXPRESSION_H
#include "../../BaseExpression.h"


class IfExpression : public BaseExpression {
    std::unique_ptr<BaseExpression> check;
    std::unique_ptr<BaseExpression> codeBlock;
public:
    std::string expressionName() override;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    IfExpression(std::unique_ptr<BaseExpression> check, std::unique_ptr<BaseExpression> codeBlock);
};


#endif //PHISILANDINTERPRETER_IFEXPRESSION_H
