//
// Created by Ezra Golombek on 24/11/2025.
//

#ifndef PHISILANDINTERPRETER_VOIDEXPRESSION_H
#define PHISILANDINTERPRETER_VOIDEXPRESSION_H
#include "expressions/BaseExpression.h"


class VoidExpression : public BaseExpression {
public:
    std::string expressionName() override {
        return "void";
    }

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override {
        return std::make_unique<VoidExpression>(*this);
    }

    std::string interpertAsString(std::shared_ptr<Scope> scope) override {
        return "You just printed… nothing. Congratulations, you've invented silence.";
    }
};


#endif //PHISILANDINTERPRETER_VOIDEXPRESSION_H
