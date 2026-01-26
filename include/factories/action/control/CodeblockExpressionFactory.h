//
// Created by Ezra Golombek on 05/11/2025.
//

#ifndef PHISILANDINTERPRETER_CODEBLOCKEXPRESSIONFACTORY_H
#define PHISILANDINTERPRETER_CODEBLOCKEXPRESSIONFACTORY_H
#include "../../Factory.h"
#include "../../../base/Scope.h"


class CodeblockExpressionFactory  : public Factory{
public:
    ~CodeblockExpressionFactory() override = default;

    std::string startToken() override;

    std::string endToken() override;

    int indexStart() override;

    int paramSize() override;



    std::unique_ptr<BaseExpression> generate(std::deque<std::unique_ptr<BaseExpression>> &arguments, std::shared_ptr<Scope>& scope) override;
};


#endif //PHISILANDINTERPRETER_CODEBLOCKEXPRESSIONFACTORY_H