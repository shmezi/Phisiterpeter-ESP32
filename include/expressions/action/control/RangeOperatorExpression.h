//
// Created by Ezra Golombek on 03/12/2025.
//

#ifndef PHISITERPETER_ESP32_RANGEEXPRESSION_H
#define PHISITERPETER_ESP32_RANGEEXPRESSION_H
#include "expressions/Expression.h"


class RangeOperatorExpression : public Expression {
    std::unique_ptr<Expression> first;
    std::unique_ptr<Expression> second;

public:
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    RangeOperatorExpression(std::unique_ptr<Expression> first, std::unique_ptr<Expression> second);

};


#endif //PHISITERPETER_ESP32_RANGEEXPRESSION_H
