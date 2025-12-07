//
// Created by Ezra Golombek on 02/12/2025.
//

#ifndef PHISITERPETER_ESP32_WHILEEXPRESSION_H
#define PHISITERPETER_ESP32_WHILEEXPRESSION_H
#include <memory>

#include "expressions/Expression.h"


class WhileExpression : public Expression {
    std::unique_ptr<Expression> check;
    std::unique_ptr<Expression> codeBlock;


public:
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    WhileExpression(std::unique_ptr<Expression> check, std::unique_ptr<Expression> codeBlock);
};


#endif //PHISITERPETER_ESP32_WHILEEXPRESSION_H
