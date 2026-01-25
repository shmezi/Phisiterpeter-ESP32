//
// Created by Ezra Golombek on 01/12/2025.
//

#include "../../../../include/factories/game/functions/StatusLEDExpressionFactory.h"

#include <algorithm>

#include "../../../../include/expressions/game/functions/StatusLEDExpression.h"

std::string StatusLEDExpressionFactory::startToken() {
    return "status";
}

int StatusLEDExpressionFactory::indexStart() {
    return 0;
}

int StatusLEDExpressionFactory::paramSize() {
    return 3;
}

std::unique_ptr<Expression> StatusLEDExpressionFactory::generate(
    std::deque<std::unique_ptr<Expression> > &arguments,
    std::shared_ptr<Scope> &scope) {
    return std::make_unique<StatusLEDExpression>(std::move(arguments[0]), std::move(arguments[1]),
                                                 std::move(arguments[2]));
}
