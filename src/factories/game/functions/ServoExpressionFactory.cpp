//
// Created by Ezra Golombek on 13/03/2026.
//

#include "../../../../include/factories/game/functions/ServoExpressionFactory.h"

#include "expressions/game/functions/ServoExpression.h"

std::string ServoExpressionFactory::startToken() {
    return "servo";
}

int ServoExpressionFactory::indexStart() {
    return 0;
}

int ServoExpressionFactory::paramSize() {
    return 2;
}

std::unique_ptr<Expression> ServoExpressionFactory::generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                                   std::shared_ptr<Scope> &scope) {
    return std::make_unique<ServoExpression>(std::move(arguments[0]), std::move(arguments[1]));
}
