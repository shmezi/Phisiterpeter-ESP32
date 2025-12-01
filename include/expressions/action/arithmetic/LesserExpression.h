//
// Created by Ezra Golombek on 30/11/2025.
//

#ifndef PHISILANDINTERPRETER_LESSEREXPRESSION_H
#define PHISILANDINTERPRETER_LESSEREXPRESSION_H
#include "expressions/Expression.h"


class LesserExpression : public Expression {
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

public:
    std::unique_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string expressionName() override { return "Greater"; };

    LesserExpression(std::unique_ptr<Expression> right, std::unique_ptr<Expression> left);

    ~LesserExpression() override = default;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
};

#endif //PHISILANDINTERPRETER_LESSEREXPRESSION_H