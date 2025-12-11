//
// Created by Ezra Golombek on 11/12/2025.
//

#ifndef PHISITERPETER_ESP32_ONRESULTEXPRESSION_H
#define PHISITERPETER_ESP32_ONRESULTEXPRESSION_H
#include "expressions/Expression.h"


class OnEventExpression : public Expression {
    std::shared_ptr<Expression> eventId;
    std::shared_ptr<Expression> codeBlock;

public:
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    OnEventExpression(std::unique_ptr<Expression> eventId, std::unique_ptr<Expression> codeBlock);
};


#endif //PHISITERPETER_ESP32_ONRESULTEXPRESSION_H
