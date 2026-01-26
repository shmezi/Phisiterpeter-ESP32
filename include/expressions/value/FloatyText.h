//
// Created by Ezra Golombek on 02/11/2025.
//

#ifndef PHISILANDINTERPRETER_FLOATYTEXT_H
#define PHISILANDINTERPRETER_FLOATYTEXT_H
#include <string>
#include <utility>

#include "../BaseExpression.h"
#include "base/Scope.h"


class FloatyText : public BaseExpression {
public:
    std::string actualFloatyText;
    std::string expressionName() override { return "variable"; };



    explicit FloatyText(std::string contents) : actualFloatyText(std::move(contents)){
    };

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    std::string instanceId() override;

 };


#endif //PHISILANDINTERPRETER_FLOATYTEXT_H
