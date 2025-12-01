//
// Created by Ezra Golombek on 30/11/2025.
//

#ifndef PHISILANDINTERPRETER_GREATEREXPRESSION_H
#define PHISILANDINTERPRETER_GREATEREXPRESSION_H
#include "expressions/Expression.h"


class GreaterExpression : public Expression {
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

public:
    std::unique_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string expressionName() override { return "Greater"; };

    GreaterExpression(std::unique_ptr<Expression> right, std::unique_ptr<Expression> left);

    ~GreaterExpression() override = default;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
};


#endif //PHISILANDINTERPRETER_GREATEREXPRESSION_H