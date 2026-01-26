//
// Created by Ezra Golombek on 02/12/2025.
//

#ifndef PHISITERPETER_ESP32_WHILEEXPRESSION_H
#define PHISITERPETER_ESP32_WHILEEXPRESSION_H
#include <memory>

#include "expressions/BaseExpression.h"


class WhileExpression : public BaseExpression {
    std::unique_ptr<BaseExpression> check;
    std::unique_ptr<BaseExpression> codeBlock;


public:
    std::string expressionName() override;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    WhileExpression(std::unique_ptr<BaseExpression> check, std::unique_ptr<BaseExpression> codeBlock);
};


#endif //PHISITERPETER_ESP32_WHILEEXPRESSION_H
