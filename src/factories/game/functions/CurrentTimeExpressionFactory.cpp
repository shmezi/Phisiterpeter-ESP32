//
// Created by Ezra Golombek on 07/12/2025.
//

#include "../../../../include/factories/game/functions/CurrentTimeExpressionFactory.h"

#include "../../../../include/expressions/game/functions/CurrentTimeExpression.h"

std::string CurrentTimeExpressionFactory::startToken() {
    return "now";
}

int CurrentTimeExpressionFactory::indexStart() {
    return 0;
}

int CurrentTimeExpressionFactory::paramSize() {
    return 0;
}

std::unique_ptr<Expression> CurrentTimeExpressionFactory::generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                                   std::shared_ptr<Scope> &scope) {
    return std::make_unique<CurrentTimeExpression>();
}
