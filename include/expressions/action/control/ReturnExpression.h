//
// Created by Ezra Golombek on 06/11/2025.
//

#ifndef PHISILANDINTERPRETER_RETURNEXPRESSION_H
#define PHISILANDINTERPRETER_RETURNEXPRESSION_H
#include "../../BaseExpression.h"


class ReturnExpression : public BaseExpression {
public:
    std::unique_ptr<BaseExpression> expression;

    std::string expressionName() override;


    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    std::string instanceId() override;

    explicit ReturnExpression(std::unique_ptr<BaseExpression> expression) {
        this->expression = std::move(expression);
    }
};


#endif //PHISILANDINTERPRETER_RETURNEXPRESSION_H
