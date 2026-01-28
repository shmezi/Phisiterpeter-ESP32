//
// Created by Ezra Golombek on 05/11/2025.
//

#ifndef PHISILANDINTERPRETER_CODEBLOCKEXPRESSION_H
#define PHISILANDINTERPRETER_CODEBLOCKEXPRESSION_H
#include <deque>
#include <string>

#include "Utils.h"
#include "../../Expression.h"


class CodeblockExpression : public Expression {
public:
    std::deque<std::unique_ptr<Expression> > expressions;

    ~CodeblockExpression() override = default;

    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    explicit CodeblockExpression(std::deque<std::unique_ptr<Expression> > expressions) {
        debug::print("Codeblock built with " + std::to_string(expressions.size()));

        this->expressions = std::move(expressions);
    }
};


#endif //PHISILANDINTERPRETER_CODEBLOCKEXPRESSION_H
