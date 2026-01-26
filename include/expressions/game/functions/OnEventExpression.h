//
// Created by Ezra Golombek on 11/12/2025.
//

#ifndef PHISITERPETER_ESP32_ONRESULTEXPRESSION_H
#define PHISITERPETER_ESP32_ONRESULTEXPRESSION_H
#include "expressions/BaseExpression.h"


class OnEventExpression : public BaseExpression {
    std::shared_ptr<BaseExpression> eventId;
    std::shared_ptr<BaseExpression> codeBlock;

public:
    std::string expressionName() override;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    OnEventExpression(std::unique_ptr<BaseExpression> eventId, std::unique_ptr<BaseExpression> codeBlock);
};


#endif //PHISITERPETER_ESP32_ONRESULTEXPRESSION_H
