//
// Created by Ezra Golombek on 04/12/2025.
//

#ifndef PHISITERPETER_ESP32_WRITEEXPRESSION_H
#define PHISITERPETER_ESP32_WRITEEXPRESSION_H
#include "expressions/Expression.h"


class WriteExpression  : public Expression{
    std::unique_ptr<Expression> pin;
    std::unique_ptr<Expression> value;
public:
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
    WriteExpression(std::unique_ptr<Expression> pin,std::unique_ptr<Expression> value);
};


#endif //PHISITERPETER_ESP32_WRITEEXPRESSION_H