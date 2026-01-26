//
// Created by Ezra Golombek on 07/12/2025.
//

#ifndef PHISITERPETER_ESP32_CLEARLISTEXPRESSION_H
#define PHISITERPETER_ESP32_CLEARLISTEXPRESSION_H
#include "expressions/BaseExpression.h"


class ClearListExpression : public BaseExpression {
    std::unique_ptr<BaseExpression> list;

public:
    std::string expressionName() override;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    explicit ClearListExpression(std::unique_ptr<BaseExpression> list);
};


#endif //PHISITERPETER_ESP32_CLEARLISTEXPRESSION_H
