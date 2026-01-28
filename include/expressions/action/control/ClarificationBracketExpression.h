//
// Created by Ezra Golombek on 03/11/2025.
//

#ifndef PHISILANDINTERPRETER_CLARIFICATIONBRACKETEXPRESSION_H
#define PHISILANDINTERPRETER_CLARIFICATIONBRACKETEXPRESSION_H
#include <deque>
#include <string>
#include <vector>

#include "Utils.h"
#include "../../Expression.h"


class ClarificationBracketExpression : public Expression {
public:
    std::deque<std::unique_ptr<Expression> > expressions;

    ~ClarificationBracketExpression() override = default;

    std::string expressionName() override { return "ClarificationBracket"; };

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    int expressionCount() const;

    explicit ClarificationBracketExpression(std::deque<std::unique_ptr<Expression> > expressions) {
        this->expressions = std::move(expressions);
        debug::print("Building a clarification from: ");
        for (const auto &e: this->expressions) {
            debug::print(e->expressionName());
        }
    }
};


#endif //PHISILANDINTERPRETER_CLARIFICATIONBRACKETEXPRESSION_H
