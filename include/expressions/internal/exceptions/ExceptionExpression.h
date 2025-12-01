//
// Created by Ezra Golombek on 29/11/2025.
//

#ifndef PHISILANDINTERPRETER_EXCEPTIONEXPRESSION_H
#define PHISILANDINTERPRETER_EXCEPTIONEXPRESSION_H
#include "Utils.h"
#include "expressions/Expression.h"
#include "expressions/internal/VoidExpression.h"

class ExceptionExpression : public Expression {
public:
    std::string name;
    std::string message;

    std::string expressionName() override {
        return "exception";
    };

    std::unique_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override {
        std::cout << debug::colorize("[" + name + "-Exception] - " + message, debug::Color::RED) << std::endl;
        return std::make_unique<VoidExpression>();
    }

    std::string interpertAsString(std::shared_ptr<Scope> scope) override {
        return "";
    }

    explicit ExceptionExpression(std::string name, std::string message) : name(std::move(name)),
                                                                          message(std::move(message)) {
    }
};
#endif //PHISILANDINTERPRETER_EXCEPTIONEXPRESSION_H
