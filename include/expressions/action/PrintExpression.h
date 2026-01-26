//
// Created by Ezra Golombek on 02/11/2025.
//

#ifndef PHISILANDINTERPRETER_PRINTEXPRESSION_H
#define PHISILANDINTERPRETER_PRINTEXPRESSION_H
#include "../BaseExpression.h"
#include "../value/TextExpression.h"
#include "expressions/Expression.h"


class PrintExpression : public Expression<PrintExpression> {
public:


    std::unique_ptr<BaseExpression> expression;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    explicit PrintExpression(std::unique_ptr<BaseExpression> expression) : expression(std::move(expression)) {
    }

    std::string expressionName() override { return "print"; };

    ~PrintExpression() override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    static ExpressionInfo getInfo();


    static std::unique_ptr<BaseExpression> generate(std::deque<std::unique_ptr<BaseExpression>> &arguments,
                                                std::shared_ptr<Scope> &scope);
};


#endif //PHISILANDINTERPRETER_PRINTEXPRESSION_H
