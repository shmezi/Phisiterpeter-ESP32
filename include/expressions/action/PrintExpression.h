//
// Created by Ezra Golombek on 02/11/2025.
//

#ifndef PHISILANDINTERPRETER_PRINTEXPRESSION_H
#define PHISILANDINTERPRETER_PRINTEXPRESSION_H
#include "../Expression.h"
#include "../value/TextExpression.h"


class PrintExpression : public Expression {
public:
    std::unique_ptr<Expression> expression;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    explicit PrintExpression(std::unique_ptr<Expression> expression) : expression(std::move(expression)) {
    }

    std::string expressionName() override { return "print"; };

    ~PrintExpression() override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;;
};


#endif //PHISILANDINTERPRETER_PRINTEXPRESSION_H
