//
// Created by Ezra Golombek on 07/12/2025.
//

#ifndef PHISITERPETER_ESP32_ADDTOLISTEXPRESSION_H
#define PHISITERPETER_ESP32_ADDTOLISTEXPRESSION_H
#include "expressions/BaseExpression.h"


class AddToListExpression : public BaseExpression {
    std::unique_ptr<BaseExpression> list;
    std::unique_ptr<BaseExpression> newItem;

public:
    std::string expressionName() override;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    AddToListExpression(
        std::unique_ptr<BaseExpression> list,
        std::unique_ptr<BaseExpression> newItem);
};


#endif //PHISITERPETER_ESP32_ADDTOLISTEXPRESSION_H
