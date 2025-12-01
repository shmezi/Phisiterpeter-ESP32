//
// Created by Ezra Golombek on 08/11/2025.
//

#ifndef PHISILANDINTERPRETER_ANDEXPRESSION_H
#define PHISILANDINTERPRETER_ANDEXPRESSION_H
#include "expressions/Expression.h"


class AndExpression : public Expression{
    std::unique_ptr<Expression> right; std::unique_ptr<Expression> left;
public:

    std::string expressionName() override;

    std::unique_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
    AndExpression(std::unique_ptr<Expression> right, std::unique_ptr<Expression> left);

};


#endif //PHISILANDINTERPRETER_ANDEXPRESSION_H