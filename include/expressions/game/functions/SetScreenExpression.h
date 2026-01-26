//
// Created by Ezra Golombek on 22/01/2026.
//

#ifndef PHISITERPETER_ESP32_SETSCREENEXPRESSION_H
#define PHISITERPETER_ESP32_SETSCREENEXPRESSION_H
#include "expressions/BaseExpression.h"


class SetScreenExpression : public BaseExpression {
public:
    std::unique_ptr<BaseExpression> screen;

    std::string expressionName() override;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    explicit SetScreenExpression( std::unique_ptr<BaseExpression> screen);
};


#endif //PHISITERPETER_ESP32_SETSCREENEXPRESSION_H
