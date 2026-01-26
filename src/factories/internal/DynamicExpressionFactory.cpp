//
// Created by Ezra Golombek on 06/11/2025.
//

#include "../../../include/factories/internal/DynamicExpressionFactory.h"

#include "Utils.h"
#include "expressions/internal/DynamicExpression.h"

std::string DynamicExpressionFactory::startToken() {
    return this->internal_tokenIdentifier;
}


int DynamicExpressionFactory::indexStart() {
    return 0;
}

int DynamicExpressionFactory::paramSize() {
    return static_cast<int>(this->internal_argument_names.size());
}

std::string DynamicExpressionFactory::endToken() {
    return Factory::endToken();
}


std::unique_ptr<BaseExpression> DynamicExpressionFactory::generate(
    std::deque<std::unique_ptr<BaseExpression> > &arguments, std::shared_ptr<Scope> &scope) {
    std::deque<PassedArgument> toBePassedArguments;

    for (int i = 0; i < arguments.size() ; ++i) {

        auto passedArgument = PassedArgument(std::move(arguments[i]), internal_argument_names[i]);
        toBePassedArguments.emplace_back(std::move(passedArgument));
    }
    return std::make_unique<DynamicExpression>(std::move(toBePassedArguments), codeBlock);
}
