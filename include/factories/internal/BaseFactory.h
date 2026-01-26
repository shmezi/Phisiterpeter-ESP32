//
// Created by Ezra Golombek on 26/01/2026.
//

#ifndef PHISITERPETER_ESP32_BASEFACTORY_H
#define PHISITERPETER_ESP32_BASEFACTORY_H
#include "../../../../../.platformio/packages/toolchain-riscv32-esp/riscv32-esp-elf/include/c++/14.2.0/functional"
#include "factories/Factory.h"
#include "expressions/BaseExpression.h"

class BaseFactory : public Factory {
    std::string passStartToken;
    int passIndexStart;
    int passParamSize;
    std::string passEndToken;

    std::function<std::unique_ptr<BaseExpression>(
        std::deque<std::unique_ptr<BaseExpression> >,
        std::shared_ptr<Scope>)> passGenerator;

public:
    std::string startToken() override;

    int indexStart() override;

    int paramSize() override;

    std::string endToken() override;

    std::unique_ptr<BaseExpression> generate(
        std::deque<std::unique_ptr<BaseExpression> > &arguments,
        std::shared_ptr<Scope> &scope) override;

    BaseFactory(
        const std::string &startToken,
        const int indexStart,
        const int paramSize,
        const std::string &endToken,
        const std::function<std::unique_ptr<BaseExpression>(
            std::deque<std::unique_ptr<BaseExpression> >,
            std::shared_ptr<Scope>)> &func) {
        passStartToken = startToken;
        passIndexStart = indexStart;
        passParamSize = paramSize;
        passEndToken = endToken;
        passGenerator = func;
    }
};


#endif //PHISITERPETER_ESP32_BASEFACTORY_H
