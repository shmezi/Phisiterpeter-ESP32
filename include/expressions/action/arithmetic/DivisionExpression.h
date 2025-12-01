//
// Created by Ezra Golombek on 30/11/2025.
//

#ifndef PHISILANDINTERPRETER_DIVISIONEXPRESSION_H
#define PHISILANDINTERPRETER_DIVISIONEXPRESSION_H
#include "expressions/Expression.h"


class DivisionExpression : public Expression {
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

public:
    std::unique_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string expressionName() override { return "Division"; };

    DivisionExpression(std::unique_ptr<Expression> right, std::unique_ptr<Expression> left);

    ~DivisionExpression() override = default;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
};

#endif //PHISILANDINTERPRETER_DIVISIONEXPRESSION_H
