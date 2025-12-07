//
// Created by Ezra Golombek on 30/10/2025.
//

#ifndef PHISILANDINTERPRETER_NUMBEREXPRESSION_H
#define PHISILANDINTERPRETER_NUMBEREXPRESSION_H
#include <string>

#include "../Expression.h"

class NumberExpression : public Expression, public std::enable_shared_from_this<NumberExpression> {
public:
    explicit NumberExpression(int contents);

    int contents;

    ~NumberExpression() override = default;

    std::string expressionName() override { return "number"; }

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    std::shared_ptr<Expression>
    addition(std::shared_ptr<Expression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::shared_ptr<Expression>
    equal(std::shared_ptr<Expression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::shared_ptr<Expression>
    unequal(std::shared_ptr<Expression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::shared_ptr<Expression>
    greater(std::shared_ptr<Expression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::shared_ptr<Expression>
    lesser(std::shared_ptr<Expression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::shared_ptr<Expression>
    division(std::shared_ptr<Expression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::shared_ptr<Expression>
    multiply(std::shared_ptr<Expression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::shared_ptr<Expression>
    subtract(std::shared_ptr<Expression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::shared_ptr<Expression> toOperator(std::shared_ptr<Expression> &&expression,
                                           std::shared_ptr<Scope> &parentScope) override;
};

#endif //PHISILANDINTERPRETER_NUMBEREXPRESSION_H
