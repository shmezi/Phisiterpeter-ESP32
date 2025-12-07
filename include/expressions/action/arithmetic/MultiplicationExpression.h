//
// Created by Ezra Golombek on 30/11/2025.
//

#ifndef PHISILANDINTERPRETER_MULTIPICATIONEXPRESSION_H
#define PHISILANDINTERPRETER_MULTIPICATIONEXPRESSION_H
#include "expressions/Expression.h"


class MultiplicationExpression : public Expression {
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

public:
  std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string expressionName() override { return "Greater"; };

    MultiplicationExpression(std::unique_ptr<Expression> right, std::unique_ptr<Expression> left);

    ~MultiplicationExpression() override = default;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
};
#endif //PHISILANDINTERPRETER_MULTIPICATIONEXPRESSION_H