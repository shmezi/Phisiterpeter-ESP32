//
// Created by Ezra Golombek on 02/12/2025.
//

#ifndef PHISITERPETER_ESP32_WHENEXPRESSIONFACTORY_H
#define PHISITERPETER_ESP32_WHENEXPRESSIONFACTORY_H
#include "factories/Factory.h"


class WhenExpressionFactory  : public Factory{
public:
    std::string startToken() override;

    int indexStart() override;

    int paramSize() override;

    std::unique_ptr<BaseExpression> generate(std::deque<std::unique_ptr<BaseExpression>> &arguments,
        std::shared_ptr<Scope> &scope) override;
};


#endif //PHISITERPETER_ESP32_WHENEXPRESSIONFACTORY_H