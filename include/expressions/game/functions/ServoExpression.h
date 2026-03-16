//
// Created by Ezra Golombek on 13/03/2026.
//

#ifndef PHISITERPETER_ESP32_ANALOGWRITEEXPRESSION_H
#define PHISITERPETER_ESP32_ANALOGWRITEEXPRESSION_H
#include <set>

#include "expressions/Expression.h"


class ServoExpression : public Expression {
    static std::set<int> registeredPins;

public:
    std::unique_ptr<Expression> pinNumber;
    std::unique_ptr<Expression> value;
    ServoExpression(std::unique_ptr<Expression> pinNumber,
    std::unique_ptr<Expression> value);
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;
};


#endif //PHISITERPETER_ESP32_ANALOGWRITEEXPRESSION_H
