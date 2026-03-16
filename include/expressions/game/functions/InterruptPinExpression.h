//
// Created by Ezra Golombek on 16/03/2026.
//

#ifndef PHISITERPETER_ESP32_INTERUPTPINEXPRESSION_H
#define PHISITERPETER_ESP32_INTERUPTPINEXPRESSION_H
#include "expressions/Expression.h"



class InterruptPinExpression : public Expression, public std::enable_shared_from_this<InterruptPinExpression> {
public:
    std::shared_ptr<Expression> pin;
    std::shared_ptr<Expression> codeBlock;

    volatile bool interrupted = false;
    bool registered = false;
    uint32_t lastRun = 0;


    std::string expressionName() override;

    static int taskID;

    void trampoline();

    InterruptPinExpression(std::shared_ptr<Expression> pin,
                           std::shared_ptr<Expression> codeBlock) : pin(pin), codeBlock(codeBlock) {

    }

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;
};


#endif //PHISITERPETER_ESP32_INTERUPTPINEXPRESSION_H
