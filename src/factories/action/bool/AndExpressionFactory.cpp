//
// Created by Ezra Golombek on 08/11/2025.
//

#include "factories/action/bool/AndExpressionFactory.h"

#include <deque>
#include <string>

#include "expressions/action/bool/AndExpression.h"

class Scope;
class Expression;

std::string AndExpressionFactory::startToken() {
    return "and";
}

int AndExpressionFactory::indexStart() {
    return -1;
}

int AndExpressionFactory::paramSize() {
    return 2;
}

std::unique_ptr<Expression> AndExpressionFactory::generate(std::deque<std::unique_ptr<Expression>> &arguments,
    std::shared_ptr<Scope> &scope) {
    return std::make_unique<AndExpression>(std::move(arguments[0]), std::move(arguments[1]));
}
