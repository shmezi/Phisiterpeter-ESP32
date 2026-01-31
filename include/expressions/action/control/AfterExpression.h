//
// Created by Ezra Golombek on 31/01/2026.
//

#ifndef PHISITERPETER_ESP32_AFTEREXORESSION_H
#define PHISITERPETER_ESP32_AFTEREXORESSION_H
#include "expressions/Expression.h"


class AfterExpression : public Expression {
    std::unique_ptr<Expression> duration;
    std::unique_ptr<Expression> codeblock;

public:
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    AfterExpression(std::unique_ptr<Expression> duration,
                    std::unique_ptr<Expression> codeblock) : duration(std::move(duration)),
                                                             codeblock(std::move(codeblock)) {
    }
};


#endif //PHISITERPETER_ESP32_AFTEREXORESSION_H
