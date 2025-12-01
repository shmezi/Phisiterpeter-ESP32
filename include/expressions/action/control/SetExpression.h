//
// Created by Ezra Golombek on 02/11/2025.
//

#ifndef PHISILANDINTERPRETER_SETEXPRESSION_H
#define PHISILANDINTERPRETER_SETEXPRESSION_H
#include "../../Expression.h"
#include "../../value/TextExpression.h"


class SetExpression : public Expression {
    std::shared_ptr<Expression> name;
    std::shared_ptr<Expression> content;

public:
    std::unique_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;
    std::string expressionName() override {return "variable set";};
    SetExpression(std::unique_ptr<Expression> name, std::unique_ptr<Expression>);

    ~SetExpression() override = default;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
};


#endif //PHISILANDINTERPRETER_SETEXPRESSION_H
