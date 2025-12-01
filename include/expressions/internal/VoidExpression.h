//
// Created by Ezra Golombek on 24/11/2025.
//

#ifndef PHISILANDINTERPRETER_VOIDEXPRESSION_H
#define PHISILANDINTERPRETER_VOIDEXPRESSION_H
#include "expressions/Expression.h"


class VoidExpression : public Expression {
public:
    std::string expressionName() override {
        return "void";
    }

    std::unique_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override {
        return std::make_unique<VoidExpression>(*this);
    }

    std::string interpertAsString(std::shared_ptr<Scope> scope) override {
        return "";
    }
};


#endif //PHISILANDINTERPRETER_VOIDEXPRESSION_H
