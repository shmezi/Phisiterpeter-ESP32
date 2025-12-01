//
// Created by Ezra Golombek on 08/11/2025.
//

#ifndef PHISILANDINTERPRETER_IFEXPRESSION_H
#define PHISILANDINTERPRETER_IFEXPRESSION_H
#include "../../Expression.h"


class IfExpression : public Expression {
    std::unique_ptr<Expression> check;
    std::unique_ptr<Expression> codeBlock;
public:
    std::string expressionName() override;

    std::unique_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    IfExpression(std::unique_ptr<Expression> check, std::unique_ptr<Expression> codeBlock);
};


#endif //PHISILANDINTERPRETER_IFEXPRESSION_H
