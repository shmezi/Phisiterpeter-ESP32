//
// Created by Ezra Golombek on 12/06/2026.
//

#ifndef PHISITERPETER_ESP32_REMOTELOGEXPRESSION_H
#define PHISITERPETER_ESP32_REMOTELOGEXPRESSION_H
#include "expressions/Expression.h"


class RemoteLogExpression : public Expression {
    std::unique_ptr<Expression> contents;

public:
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;


    explicit RemoteLogExpression(std::unique_ptr<Expression> contents) {
        this->contents = std::move(contents);
    }
};


#endif //PHISITERPETER_ESP32_REMOTELOGEXPRESSION_H
