//
// Created by Ezra Golombek on 02/11/2025.
//

#ifndef PHISILANDINTERPRETER_SETEXPRESSION_H
#define PHISILANDINTERPRETER_SETEXPRESSION_H
#include "../../BaseExpression.h"
#include "../../value/TextExpression.h"


class SetExpression : public BaseExpression {
    std::shared_ptr<BaseExpression> name;
    std::shared_ptr<BaseExpression> content;

public:
    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;
    std::string expressionName() override {return "variable set";};
    SetExpression(std::unique_ptr<BaseExpression> name, std::unique_ptr<BaseExpression>);

    ~SetExpression() override = default;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
};


#endif //PHISILANDINTERPRETER_SETEXPRESSION_H
