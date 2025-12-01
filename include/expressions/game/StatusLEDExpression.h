//
// Created by Ezra Golombek on 01/12/2025.
//

#ifndef PHISITERPETER_ESP32_STATUSLEDEXPRESSION_H
#define PHISITERPETER_ESP32_STATUSLEDEXPRESSION_H
#include "expressions/Expression.h"


class StatusLEDExpression : public Expression {
    std::unique_ptr<Expression> r;
    std::unique_ptr<Expression> g;
    std::unique_ptr<Expression> b;

public:
    std::string expressionName() override;

    std::unique_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    StatusLEDExpression(std::unique_ptr<Expression> r, std::unique_ptr<Expression> g, std::unique_ptr<Expression> b);
};


#endif //PHISITERPETER_ESP32_STATUSLEDEXPRESSION_H
