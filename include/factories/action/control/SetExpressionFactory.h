//
// Created by Ezra Golombek on 02/11/2025.
//

#ifndef PHISILANDINTERPRETER_SETEXPRESSIONFACTORY_H
#define PHISILANDINTERPRETER_SETEXPRESSIONFACTORY_H
#include "../../../base/Scope.h"
#include "../../Factory.h"


class SetExpressionFactory :public Factory {
public:
    std::string startToken() override;

    int indexStart() override;

    int paramSize() override;

    std::unique_ptr<Expression> generate(std::deque<std::unique_ptr<Expression>> &arguments, std::shared_ptr<Scope> &scope) override;

    ~SetExpressionFactory() override = default;
};


#endif //PHISILANDINTERPRETER_SETEXPRESSIONFACTORY_H