//
// Created by Ezra Golombek on 07/12/2025.
//

#ifndef PHISITERPETER_ESP32_ADDTOLISTEXPRESSION_H
#define PHISITERPETER_ESP32_ADDTOLISTEXPRESSION_H
#include "expressions/Expression.h"


class AddToListExpression : public Expression {
    std::unique_ptr<Expression> list;
    std::unique_ptr<Expression> newItem;

public:
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    AddToListExpression(
        std::unique_ptr<Expression> list,
        std::unique_ptr<Expression> newItem);
};


#endif //PHISITERPETER_ESP32_ADDTOLISTEXPRESSION_H
