//
// Created by Ezra Golombek on 02/11/2025.
//

#ifndef PHISILANDINTERPRETER_PRINTEXPRESSIONFACTORY_H
#define PHISILANDINTERPRETER_PRINTEXPRESSIONFACTORY_H
#include "../base/Scope.h"
#include "Factory.h"


class PrintExpressionFactory : public Factory{
public:
    std::string startToken() override;

    int indexStart() override;

    int paramSize() override;

    std::unique_ptr<BaseExpression> generate(std::deque<std::unique_ptr<BaseExpression>> &arguments, std::shared_ptr<Scope> &scope) override;
};


#endif //PHISILANDINTERPRETER_PRINTEXPRESSIONFACTORY_H