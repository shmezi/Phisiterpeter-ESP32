//
// Created by Ezra Golombek on 08/11/2025.
//

#ifndef PHISILANDINTERPRETER_OREXPRESSIONFACTORY_H
#define PHISILANDINTERPRETER_OREXPRESSIONFACTORY_H
#include "factories/Factory.h"


class OrExpressionFactory : public Factory{
public:
    std::string startToken() override;

    int indexStart() override;

    int paramSize() override;

    std::unique_ptr<BaseExpression> generate(std::deque<std::unique_ptr<BaseExpression>> &arguments,
        std::shared_ptr<Scope> &scope) override;
};


#endif //PHISILANDINTERPRETER_OREXPRESSIONFACTORY_H