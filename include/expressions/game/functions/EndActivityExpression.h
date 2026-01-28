//
// Created by Ezra Golombek on 28/01/2026.
//

#ifndef PHISITERPETER_ESP32_ENDACTIVITYEXPRESSION_H
#define PHISITERPETER_ESP32_ENDACTIVITYEXPRESSION_H
#include "expressions/Expression.h"


class EndActivityExpression : public Expression{
public:
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
};


#endif //PHISITERPETER_ESP32_ENDACTIVITYEXPRESSION_H