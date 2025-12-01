//
// Created by Ezra Golombek on 07/11/2025.
//

#ifndef PHISILANDINTERPRETER_BOOLEANEXPRESSION_H
#define PHISILANDINTERPRETER_BOOLEANEXPRESSION_H
#include "../Expression.h"


class BooleanExpression : public Expression {


public:
    std::string expressionName() override;
    bool contents;
    std::unique_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    explicit BooleanExpression(const bool contents) : contents(contents) {
    }

    ~BooleanExpression() override = default;

    std::string instanceId() override;

    std::unique_ptr<Expression> notOperator(std::shared_ptr<Scope> &parentScope) override;

    std::unique_ptr<Expression> andOperator(std::unique_ptr<Expression> &&expression,
        std::shared_ptr<Scope> &parentScope) override;

    std::unique_ptr<Expression> orOperator(std::unique_ptr<Expression> &&expression,
        std::shared_ptr<Scope> &parentScope) override;
};


#endif //PHISILANDINTERPRETER_BOOLEANEXPRESSION_H
