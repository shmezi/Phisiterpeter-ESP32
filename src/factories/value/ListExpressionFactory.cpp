//
// Created by Ezra Golombek on 07/12/2025.
//

#include "ListExpressionFactory.h"

#include <algorithm>

#include "Utils.h"
#include "expressions/action/control/ValueHoldExpression.h"
#include "expressions/value/ListExpression.h"

std::string ListExpressionFactory::startToken() {
    return "[";
}

std::string ListExpressionFactory::endToken() {
    return "]";
}

int ListExpressionFactory::indexStart() {
    return 0;
}

int ListExpressionFactory::paramSize() {
    return 0;
}

std::unique_ptr<BaseExpression> ListExpressionFactory::generate(std::deque<std::unique_ptr<BaseExpression> > &arguments,
                                                            std::shared_ptr<Scope> &scope) {
    auto expressions = std::deque<std::shared_ptr<BaseExpression> >();
    for (auto &arg: arguments) {
        expressions.push_back(arg->interpret(scope));
    }
    debug::print("Success,created the list with the arguments!");

    return std::make_unique<ValueHoldExpression>(std::make_shared<ListExpression>(expressions));
}
