//
// Created by Ezra Golombek on 02/11/2025.
//

#ifndef PHISILANDINTERPRETER_TEXTEXPRESSION_H
#define PHISILANDINTERPRETER_TEXTEXPRESSION_H
#include <string>

#include "../Expression.h"


class TextExpression : public Expression {
    std::string contents;

public:
    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    explicit TextExpression(std::string contents) : contents(std::move(contents)){};

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
    std::string expressionName() override {return "text";};
    ~TextExpression() override = default;

    std::shared_ptr<Expression>
    addition(std::shared_ptr<Expression> &&expression, std::shared_ptr<Scope> &parentScope) override;
};


#endif //PHISILANDINTERPRETER_TEXTEXPRESSION_H
