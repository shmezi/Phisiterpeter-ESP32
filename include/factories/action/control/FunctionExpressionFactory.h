//
// Created by Ezra Golombek on 06/11/2025.
//

#ifndef PHISILANDINTERPRETER_FUNCTIONEXPRESSIONFACTORY_H
#define PHISILANDINTERPRETER_FUNCTIONEXPRESSIONFACTORY_H
#include "../../Factory.h"
#include "../../../base/Scope.h"


class FunctionExpressionFactory : public Factory {
public:
    std::string startToken() override;

    int indexStart() override;

    int paramSize() override;

    std::unique_ptr<BaseExpression> generate(std::deque<std::unique_ptr<BaseExpression>> &arguments, std::shared_ptr<Scope> &scope) override;
};


#endif //PHISILANDINTERPRETER_FUNCTIONEXPRESSIONFACTORY_H