//
// Created by Ezra Golombek on 22/01/2026.
//

#ifndef PHISITERPETER_ESP32_SETSCREENEXPRESSION_H
#define PHISITERPETER_ESP32_SETSCREENEXPRESSION_H
#include "expressions/Expression.h"


class SetScreenExpression : public Expression {
public:
    std::unique_ptr<Expression> screen;

    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    explicit SetScreenExpression( std::unique_ptr<Expression> screen);
};


#endif //PHISITERPETER_ESP32_SETSCREENEXPRESSION_H
