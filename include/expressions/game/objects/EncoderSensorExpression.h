//
// Created by Ezra Golombek on 22/01/2026.
//

#ifndef PHISITERPETER_ESP32_ENCODERSENSOREXPRESSION_H
#define PHISITERPETER_ESP32_ENCODERSENSOREXPRESSION_H

#include "expressions/Expression.h"


class EncoderSensorExpression : public Expression {
    bool first = true;
public:
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;


    std::string interpertAsString(std::shared_ptr<Scope> scope) override;
};


#endif //PHISITERPETER_ESP32_ENCODERSENSOREXPRESSION_H
