//
// Created by Ezra Golombek on 30/11/2025.
//

#ifndef PHISILANDINTERPRETER_UNEQUALEXPRESSION_H
#define PHISILANDINTERPRETER_UNEQUALEXPRESSION_H
#include "expressions/Expression.h"


class UnEqualExpression : public Expression {
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

public:
    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string expressionName() override { return "Greater"; };

    UnEqualExpression(std::unique_ptr<Expression> right, std::unique_ptr<Expression> left);

    ~UnEqualExpression() override = default;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
};

#endif //PHISILANDINTERPRETER_UNEQUALEXPRESSION_H
