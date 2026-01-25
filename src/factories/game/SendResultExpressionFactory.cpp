//
// Created by Ezra Golombek on 10/12/2025.
//

#include "../../../include/factories/game/functions/SendResultExpressionFactory.h"

#include <algorithm>

#include "../../../include/expressions/game/functions/SendResultExpression.h"

std::string SendResultExpressionFactory::startToken() {
    return "sendResult";
}

int SendResultExpressionFactory::indexStart() {
    return 0;
}

int SendResultExpressionFactory::paramSize() {
    return 2;
}

std::unique_ptr<Expression> SendResultExpressionFactory::generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                                  std::shared_ptr<Scope> &scope) {
    return std::make_unique<SendResultExpression>(std::move(arguments[0]), std::move(arguments[1]));
}
