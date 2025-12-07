//
// Created by Ezra Golombek on 30/11/2025.
//

#ifndef PHISILANDINTERPRETER_EQUALSEXPRESSION_H
#define PHISILANDINTERPRETER_EQUALSEXPRESSION_H
#include "expressions/Expression.h"


class EqualsExpression : public Expression {
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

public:
   std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string expressionName() override { return "Equals"; };

    EqualsExpression(std::unique_ptr<Expression> right, std::unique_ptr<Expression> left);

    ~EqualsExpression() override = default;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
};


#endif //PHISILANDINTERPRETER_EQUALSEXPRESSION_H