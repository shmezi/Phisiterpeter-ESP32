//
// Created by Ezra Golombek on 13/03/2026.
//

#ifndef PHISITERPETER_ESP32_ANALOGWRITEEXPRESSIONFACTORY_H
#define PHISITERPETER_ESP32_ANALOGWRITEEXPRESSIONFACTORY_H
#include "factories/Factory.h"


class ServoExpressionFactory : public Factory{
public:
    std::string startToken() override;

    int indexStart() override;

    int paramSize() override;

    std::unique_ptr<Expression> generate(std::deque<std::unique_ptr<Expression>> &arguments,
        std::shared_ptr<Scope> &scope) override;
};


#endif //PHISITERPETER_ESP32_ANALOGWRITEEXPRESSIONFACTORY_H