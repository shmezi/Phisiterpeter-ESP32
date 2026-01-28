//
// Created by Ezra Golombek on 28/01/2026.
//

#ifndef PHISITERPETER_ESP32_ENDACTIVITYEXPRESSIONFACTORY_H
#define PHISITERPETER_ESP32_ENDACTIVITYEXPRESSIONFACTORY_H
#include "factories/Factory.h"


class EndActivityExpressionFactory : public Factory{
public:
    std::string startToken() override;

    int indexStart() override;

    int paramSize() override;

    std::unique_ptr<Expression> generate(std::deque<std::unique_ptr<Expression>> &arguments,
        std::shared_ptr<Scope> &scope) override;
};


#endif //PHISITERPETER_ESP32_ENDACTIVITYEXPRESSIONFACTORY_H