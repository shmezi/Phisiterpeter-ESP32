//
// Created by Ezra Golombek on 06/11/2025.
//

#ifndef PHISILANDINTERPRETER_RETURNEXPRESSIONFACTORY_H
#define PHISILANDINTERPRETER_RETURNEXPRESSIONFACTORY_H
#include "../../Factory.h"
#include "../../../base/Scope.h"


class ReturnExpressionFactory  :public Factory{
public:
    std::string startToken() override;

    int indexStart() override;

    int paramSize() override;

    std::unique_ptr<Expression> generate(std::deque<std::unique_ptr<Expression>> &arguments, std::shared_ptr<Scope> &scope) override;
};


#endif //PHISILANDINTERPRETER_RETURNEXPRESSIONFACTORY_H