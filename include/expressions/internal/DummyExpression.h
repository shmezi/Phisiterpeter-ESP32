//
// Created by Ezra Golombek on 05/11/2025.
//

#ifndef PHISILANDINTERPRETER_DummyExpression_H
#define PHISILANDINTERPRETER_DummyExpression_H
#include <string>

#include "../BaseExpression.h"
#include "Utils.h"

/**
 * StartExpression is a VERY special expression that can not be created without other expressions.
 * It serves as a temporary indicator for the interpreter to find the start of an expression for very specific types.
 */

class DummyExpression : public BaseExpression {

public:

    ~DummyExpression() override = default;

    std::string expressionName() override {
        return "ide"; //Internal dummy expression
    }

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override {
        debug::error("An internal DummyExpression was interpreted even though it is for internal use only!");
        return nullptr;
    }


    std::string interpertAsString(std::shared_ptr<Scope> scope) override {
        const auto v = "An internal DummyExpression should not be converted to a string representation";
        debug::error(v);
        return v;
    }
};


#endif //PHISILANDINTERPRETER_DummyExpression_H
