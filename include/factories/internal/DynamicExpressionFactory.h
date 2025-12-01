//
// Created by Ezra Golombek on 06/11/2025.
//

#ifndef PHISILANDINTERPRETER_DYNAMICEXPRESSIONFACTORY_H
#define PHISILANDINTERPRETER_DYNAMICEXPRESSIONFACTORY_H
#include <list>

#include "../Factory.h"

#include <utility>
#include <vector>

#include "../../base/Scope.h"
#include "expressions/action/control/CodeblockExpression.h"


class DynamicExpressionFactory : public Factory {
    std::string internal_tokenIdentifier;

    std::deque<std::string> internal_argument_names;
    std::unique_ptr<CodeblockExpression> codeBlock;

public:
    std::string startToken() override;

    int indexStart() override;

    int paramSize() override;



    std::unique_ptr<Expression> generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                         std::shared_ptr<Scope> &scope) override;

    DynamicExpressionFactory(
        std::string tokenIdentifier,
        const std::deque<std::string>& paramNames,
        std::unique_ptr<CodeblockExpression> codeBlock)
        : internal_tokenIdentifier(std::move(tokenIdentifier)),
          internal_argument_names(paramNames), codeBlock(std::move(codeBlock)) {
    }
};


#endif //PHISILANDINTERPRETER_DYNAMICEXPRESSIONFACTORY_H
