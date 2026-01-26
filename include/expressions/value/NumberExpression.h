//
// Created by Ezra Golombek on 30/10/2025.
//

#ifndef PHISILANDINTERPRETER_NUMBEREXPRESSION_H
#define PHISILANDINTERPRETER_NUMBEREXPRESSION_H
#include <string>

#include "../BaseExpression.h"

class NumberExpression : public BaseExpression, public std::enable_shared_from_this<NumberExpression> {
public:
    explicit NumberExpression(float contents);

    float contents;

    ~NumberExpression() override = default;

    std::string expressionName() override { return "number"; }

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    std::shared_ptr<BaseExpression>
    addition(std::shared_ptr<BaseExpression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::shared_ptr<BaseExpression>
    equal(std::shared_ptr<BaseExpression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::shared_ptr<BaseExpression>
    unequal(std::shared_ptr<BaseExpression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::shared_ptr<BaseExpression>
    greater(std::shared_ptr<BaseExpression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::shared_ptr<BaseExpression>
    lesser(std::shared_ptr<BaseExpression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::shared_ptr<BaseExpression>
    division(std::shared_ptr<BaseExpression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::shared_ptr<BaseExpression>
    multiply(std::shared_ptr<BaseExpression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::shared_ptr<BaseExpression>
    subtract(std::shared_ptr<BaseExpression> &&expression, std::shared_ptr<Scope> &parentScope) override;

    std::shared_ptr<BaseExpression> toOperator(std::shared_ptr<BaseExpression> &&expression,
                                           std::shared_ptr<Scope> &parentScope) override;
};

#endif //PHISILANDINTERPRETER_NUMBEREXPRESSION_H
