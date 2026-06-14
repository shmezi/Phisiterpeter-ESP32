//
// Created by Ezra Golombek on 16/03/2026.
//

#ifndef PHISITERPETER_ESP32_INTERUPTPINEXPRESSION_H
#define PHISITERPETER_ESP32_INTERUPTPINEXPRESSION_H
#include <utility>

#include "Utils.h"
#include "expressions/Expression.h"
#include "logging/Logger.h"


struct ISRArgs;

class InterruptPinExpression : public Expression, public std::enable_shared_from_this<InterruptPinExpression> {
public:
    std::shared_ptr<Expression> pin;
    std::shared_ptr<Expression> codeBlock;

    volatile bool interrupted = false;
    bool registered = false;
    uint32_t lastRun = 0;


    std::string expressionName() override;

    int taskID = -2;

    void trampoline(int id);

    InterruptPinExpression(
        std::shared_ptr<Expression> pin,
        std::shared_ptr<Expression> codeBlock) : pin(std::move(pin)), codeBlock(std::move(codeBlock)) {
    }

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    ~InterruptPinExpression() override {
        Logger::log("deleting interrupt");
    }
};


#endif //PHISITERPETER_ESP32_INTERUPTPINEXPRESSION_H
