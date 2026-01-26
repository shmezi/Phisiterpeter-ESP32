//
// Created by Ezra Golombek on 05/11/2025.
//

#ifndef PHISILANDINTERPRETER_STARTEXPRESSION_H
#define PHISILANDINTERPRETER_STARTEXPRESSION_H
#include <string>

#include "../BaseExpression.h"
#include "Utils.h"

/**
 * StartExpression is a VERY special expression that can not be created without other expressions.
 * It serves as a temporary indicator for the interpreter to find the start of an expression for very specific types.
 */
class StartExpression : public BaseExpression {
public:
    ~StartExpression() override = default;

    std::string expressionName() override {
        return "ise"; //Internal start expression
    }

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override {
        debug::error("An internal StartExpression was interpreted even though it is for internal use only!");
        return nullptr;
    }


    std::string interpertAsString(std::shared_ptr<Scope> scope) override {
        const auto v = "An internal StartExpression should not be converted to a string representation";
        debug::error(v);
        return v;
    }
};


#endif //PHISILANDINTERPRETER_STARTEXPRESSION_H
