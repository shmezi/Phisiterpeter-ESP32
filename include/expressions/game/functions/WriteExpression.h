//
// Created by Ezra Golombek on 04/12/2025.
//

#ifndef PHISITERPETER_ESP32_WRITEEXPRESSION_H
#define PHISITERPETER_ESP32_WRITEEXPRESSION_H
#include "expressions/BaseExpression.h"


class WriteExpression  : public BaseExpression{
    std::unique_ptr<BaseExpression> pin;
    std::unique_ptr<BaseExpression> value;
public:
    std::string expressionName() override;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
    WriteExpression(std::unique_ptr<BaseExpression> pin,std::unique_ptr<BaseExpression> value);
};


#endif //PHISITERPETER_ESP32_WRITEEXPRESSION_H