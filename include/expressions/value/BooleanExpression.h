//
// Created by Ezra Golombek on 07/11/2025.
//

#ifndef PHISILANDINTERPRETER_BOOLEANEXPRESSION_H
#define PHISILANDINTERPRETER_BOOLEANEXPRESSION_H
#include "../BaseExpression.h"


class BooleanExpression : public BaseExpression {


public:
    std::string expressionName() override;
    bool contents;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    explicit BooleanExpression(const bool contents) : contents(contents) {
    }

    ~BooleanExpression() override = default;

    std::string instanceId() override;

    std::shared_ptr<BaseExpression> notOperator(std::shared_ptr<Scope> &parentScope) override;

    std::shared_ptr<BaseExpression> andOperator(std::shared_ptr<BaseExpression> &&expression,
                                            std::shared_ptr<Scope> &parentScope) override;

    std::shared_ptr<BaseExpression> orOperator(std::shared_ptr<BaseExpression> &&expression,
                                           std::shared_ptr<Scope> &parentScope) override;
};


#endif //PHISILANDINTERPRETER_BOOLEANEXPRESSION_H
