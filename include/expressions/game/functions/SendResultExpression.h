//
// Created by Ezra Golombek on 10/12/2025.
//

#ifndef PHISITERPETER_ESP32_SENDRESULTEXPRESSION_H
#define PHISITERPETER_ESP32_SENDRESULTEXPRESSION_H
#include "expressions/Expression.h"


class SendResultExpression : public Expression {
    std::unique_ptr<Expression> name;
    std::unique_ptr<Expression> value;

public:
    static std::string nextMessage;
    static std::string prevMessage;

    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    SendResultExpression(std::unique_ptr<Expression> name,
                         std::unique_ptr<Expression> value);
};


#endif //PHISITERPETER_ESP32_SENDRESULTEXPRESSION_H
