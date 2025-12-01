//
// Created by Ezra Golombek on 30/10/2025.
//

#ifndef PHISILANDINTERPRETER_ADDITIONEXPRESSION_H
#define PHISILANDINTERPRETER_ADDITIONEXPRESSION_H
#include <string>

#include "../../Expression.h"


class AdditionExpression : public Expression {
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

public:
    std::unique_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string expressionName() override {return "Addition";};
    AdditionExpression(std::unique_ptr<Expression> right, std::unique_ptr<Expression> left);

    ~AdditionExpression() override = default;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
};


#endif //PHISILANDINTERPRETER_ADDITIONEXPRESSION_H
