//
// Created by Ezra Golombek on 06/11/2025.
//

#ifndef PHISILANDINTERPRETER_RETURNEXPRESSION_H
#define PHISILANDINTERPRETER_RETURNEXPRESSION_H
#include "../../Expression.h"


class ReturnExpression : public Expression {
public:
    std::unique_ptr<Expression> expression;

    std::string expressionName() override;


    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    std::string instanceId() override;

    explicit ReturnExpression(std::unique_ptr<Expression> expression) {
        this->expression = std::move(expression);
    }
};


#endif //PHISILANDINTERPRETER_RETURNEXPRESSION_H
