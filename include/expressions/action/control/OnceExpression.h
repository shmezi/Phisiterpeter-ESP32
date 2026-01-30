//
// Created by Ezra Golombek on 29/01/2026.
//

#ifndef PHISITERPETER_ESP32_ONCEEXPRESSION_H
#define PHISITERPETER_ESP32_ONCEEXPRESSION_H
#include "expressions/Expression.h"

struct SharedBool {
    bool hasRun;
};

class OnceExpression : public Expression {
    std::shared_ptr<Expression> condition;
    std::shared_ptr<Expression> codeblock;
    bool hasBeenInterpreted = false;
    std::shared_ptr<SharedBool> hasRun = std::make_shared<SharedBool>(false);

public:
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    OnceExpression(std::unique_ptr<Expression> condition,
                   std::unique_ptr<Expression> codeblock) : condition(std::shared_ptr(std::move(condition))),
                                                            codeblock(std::shared_ptr(std::move(codeblock))) {
    };
};


#endif //PHISITERPETER_ESP32_ONCEEXPRESSION_H
