//
// Created by Ezra Golombek on 11/11/2025.
//

#ifndef PHISILANDINTERPRETER_NOTEXPRESSION_H
#define PHISILANDINTERPRETER_NOTEXPRESSION_H
#include "expressions/Expression.h"


class NotExpression : public Expression {
    std::unique_ptr<Expression> contents;

public:
    std::string expressionName() override;

    std::unique_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    explicit NotExpression(std::unique_ptr<Expression> expression) : contents(std::move(expression)) {
    }
};


#endif //PHISILANDINTERPRETER_NOTEXPRESSION_H
