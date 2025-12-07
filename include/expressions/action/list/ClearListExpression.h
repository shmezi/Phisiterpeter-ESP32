//
// Created by Ezra Golombek on 07/12/2025.
//

#ifndef PHISITERPETER_ESP32_CLEARLISTEXPRESSION_H
#define PHISITERPETER_ESP32_CLEARLISTEXPRESSION_H
#include "expressions/Expression.h"


class ClearListExpression : public Expression {
    std::unique_ptr<Expression> list;

public:
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
    ClearListExpression(std::unique_ptr<Expression> list);
};


#endif //PHISITERPETER_ESP32_CLEARLISTEXPRESSION_H
