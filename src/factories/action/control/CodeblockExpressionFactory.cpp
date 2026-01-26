//
// Created by Ezra Golombek on 05/11/2025.
//

#include "../../../../include/factories/action/control/CodeblockExpressionFactory.h"

#include "../../../../include/expressions/action/control/CodeblockExpression.h"

std::string CodeblockExpressionFactory::startToken() {
    return "{";
}

std::string CodeblockExpressionFactory::endToken() {
    return "}";
}

int CodeblockExpressionFactory::indexStart() {
    return 0;
}

int CodeblockExpressionFactory::paramSize() {
    return 0;
}



std::unique_ptr<BaseExpression> CodeblockExpressionFactory::generate(
    std::deque<std::unique_ptr<BaseExpression> > &arguments, std::shared_ptr<Scope> &scope) {
    return std::make_unique<CodeblockExpression>(std::move(arguments));
}
