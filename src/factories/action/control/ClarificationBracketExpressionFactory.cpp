//
// Created by Ezra Golombek on 04/11/2025.
//

#include "../../../../include/factories/action/control/ClarificationBracketExpressionFactory.h"

#include "../../../../include/expressions/BaseExpression.h"
#include "../../../../include/base/Scope.h"
#include "../../../../include/expressions/action/control/ClarificationBracketExpression.h"


std::string ClarificationBracketExpressionFactory::startToken() {
    return "(";
}

std::string ClarificationBracketExpressionFactory::endToken() {
    return ")";
}

int ClarificationBracketExpressionFactory::indexStart() {
    return 0;
}

int ClarificationBracketExpressionFactory::paramSize() {
    return 0;
}


std::unique_ptr<BaseExpression> ClarificationBracketExpressionFactory::generate(
    std::deque<std::unique_ptr<BaseExpression> > &arguments, std::shared_ptr<Scope> &scope) {
    return std::make_unique<ClarificationBracketExpression>(std::move(arguments));
}
