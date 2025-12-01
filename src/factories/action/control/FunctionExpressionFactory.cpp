//
// Created by Ezra Golombek on 06/11/2025.
//

#include "../../../../include/factories/action/control/FunctionExpressionFactory.h"

#include "../../../../include/expressions/action/control/ClarificationBracketExpression.h"
#include "expressions/action/control/CodeblockExpression.h"
#include "expressions/internal/DummyExpression.h"
#include "factories/internal/DynamicExpressionFactory.h"

std::string FunctionExpressionFactory::startToken() {
    return "fn";
}

int FunctionExpressionFactory::indexStart() {
    return 0;
}

int FunctionExpressionFactory::paramSize() {
    return 3;
}

std::unique_ptr<Expression> FunctionExpressionFactory::generate(
    std::deque<std::unique_ptr<Expression> > &arguments, std::shared_ptr<Scope> &scope) {
    const auto id = std::any_cast<std::string>(arguments[0]->instanceId());
    auto params = dynamic_cast<ClarificationBracketExpression *>(arguments[1].get());
    auto codeBlock = dynamic_cast<CodeblockExpression *>(arguments[2].release());

    if (!params || !codeBlock) {
        debug::error("Invalid arguments for function expression");
        return nullptr;
    }
    std::deque<std::string> paramNames;

    for (auto &param: params->expressions) {
        paramNames.emplace_back(any_cast<std::string>(param->instanceId()));
    }
    auto factory = DynamicExpressionFactory(
        id,
        paramNames,
        std::unique_ptr<CodeblockExpression>(codeBlock)
    );



    scope->keyWords.insert_or_assign(id, std::move(std::make_shared<DynamicExpressionFactory>(std::move(factory))));


    return std::make_unique<DummyExpression>();
}
