//
// Created by Ezra Golombek on 07/12/2025.
//

#ifndef PHISITERPETER_ESP32_CURRENTTIMEEXPRESSION_H
#define PHISITERPETER_ESP32_CURRENTTIMEEXPRESSION_H
#include "expressions/Expression.h"


class CurrentTimeExpression :public Expression {
public:
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
};


#endif //PHISITERPETER_ESP32_CURRENTTIMEEXPRESSION_H