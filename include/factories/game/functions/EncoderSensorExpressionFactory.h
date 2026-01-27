//
// Created by Ezra Golombek on 27/01/2026.
//

#ifndef PHISITERPETER_ESP32_ENCODERSENSOREXPRESSIONFACTORY_H
#define PHISITERPETER_ESP32_ENCODERSENSOREXPRESSIONFACTORY_H
#include "factories/Factory.h"


class EncoderSensorExpressionFactory : public Factory {
public:
    std::string startToken() override;

    int indexStart() override;

    int paramSize() override;

    std::unique_ptr<Expression> generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                         std::shared_ptr<Scope> &scope) override;
};


#endif //PHISITERPETER_ESP32_ENCODERSENSOREXPRESSIONFACTORY_H
