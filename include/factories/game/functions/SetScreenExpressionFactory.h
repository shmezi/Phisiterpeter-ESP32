//
// Created by Ezra Golombek on 22/01/2026.
//

#ifndef PHISITERPETER_ESP32_SETSCREENEXPRESSIONFACTORY_H
#define PHISITERPETER_ESP32_SETSCREENEXPRESSIONFACTORY_H
#include "factories/Factory.h"


class SetScreenExpressionFactory : public Factory{
public:
    std::string startToken() override;

    int indexStart() override;

    int paramSize() override;

    std::unique_ptr<BaseExpression> generate(std::deque<std::unique_ptr<BaseExpression>> &arguments,
        std::shared_ptr<Scope> &scope) override;
};


#endif //PHISITERPETER_ESP32_SETSCREENEXPRESSIONFACTORY_H