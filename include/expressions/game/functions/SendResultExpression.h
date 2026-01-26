//
// Created by Ezra Golombek on 10/12/2025.
//

#ifndef PHISITERPETER_ESP32_SENDRESULTEXPRESSION_H
#define PHISITERPETER_ESP32_SENDRESULTEXPRESSION_H
#include "expressions/BaseExpression.h"


class SendResultExpression : public BaseExpression {
    std::unique_ptr<BaseExpression> name;
    std::unique_ptr<BaseExpression> value;
public:
    std::string expressionName() override;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
    SendResultExpression(std::unique_ptr<BaseExpression> name,
    std::unique_ptr<BaseExpression> value);
};


#endif //PHISITERPETER_ESP32_SENDRESULTEXPRESSION_H
