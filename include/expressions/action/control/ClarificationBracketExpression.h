//
// Created by Ezra Golombek on 03/11/2025.
//

#ifndef PHISILANDINTERPRETER_CLARIFICATIONBRACKETEXPRESSION_H
#define PHISILANDINTERPRETER_CLARIFICATIONBRACKETEXPRESSION_H
#include <deque>
#include <string>
#include <vector>

#include "../../Expression.h"


class ClarificationBracketExpression : public Expression {

public:
    std::deque<std::unique_ptr<Expression> > expressions;

    ~ClarificationBracketExpression() override = default;

    std::string expressionName() override { return "ClarificationBracket"; };

    std::unique_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    int expressionCount() const;

    explicit ClarificationBracketExpression(std::deque<std::unique_ptr<Expression> > expressions) {

        this->expressions = std::move(expressions);
    }
};


#endif //PHISILANDINTERPRETER_CLARIFICATIONBRACKETEXPRESSION_H
