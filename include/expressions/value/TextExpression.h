//
// Created by Ezra Golombek on 02/11/2025.
//

#ifndef PHISILANDINTERPRETER_TEXTEXPRESSION_H
#define PHISILANDINTERPRETER_TEXTEXPRESSION_H
#include <string>

#include "../BaseExpression.h"


class TextExpression : public BaseExpression {
    std::string contents;

public:
    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    explicit TextExpression(std::string contents) : contents(std::move(contents)){};

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
    std::string expressionName() override {return "text";};
    ~TextExpression() override = default;

    std::shared_ptr<BaseExpression>
    addition(std::shared_ptr<BaseExpression> &&expression, std::shared_ptr<Scope> &parentScope) override;
};


#endif //PHISILANDINTERPRETER_TEXTEXPRESSION_H
