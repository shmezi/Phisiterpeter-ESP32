//
// Created by Ezra Golombek on 30/10/2025.
//

#ifndef PHISILANDINTERPRETER_NUMBEREXPRESSION_H
#define PHISILANDINTERPRETER_NUMBEREXPRESSION_H
#include <string>

#include "../Expression.h"

class NumberExpression : public Expression {
public:
    explicit NumberExpression(int contents);

    int contents;

    ~NumberExpression() override = default;

    std::string expressionName() override { return "number"; }

    std::unique_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    std::unique_ptr<Expression>
    addition(std::unique_ptr<Expression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::unique_ptr<Expression>
    equal(std::unique_ptr<Expression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::unique_ptr<Expression>
    unequal(std::unique_ptr<Expression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::unique_ptr<Expression>
    greater(std::unique_ptr<Expression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::unique_ptr<Expression>
    lesser(std::unique_ptr<Expression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::unique_ptr<Expression>
    division(std::unique_ptr<Expression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::unique_ptr<Expression>
    multiply(std::unique_ptr<Expression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::unique_ptr<Expression>
    subtract(std::unique_ptr<Expression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::unique_ptr<Expression> toOperator(std::unique_ptr<Expression> &&expression,
                                           std::shared_ptr<Scope> &parentScope) override;
};

#endif //PHISILANDINTERPRETER_NUMBEREXPRESSION_H
