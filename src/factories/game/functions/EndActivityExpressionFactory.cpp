//
// Created by Ezra Golombek on 28/01/2026.
//

#include "../../../../include/factories/game/functions/EndActivityExpressionFactory.h"

#include "expressions/game/functions/EndActivityExpression.h"

std::string EndActivityExpressionFactory::startToken() {
    return "endActivity";
}

int EndActivityExpressionFactory::indexStart() {
    return 0;
}

int EndActivityExpressionFactory::paramSize() {
    return 0;
}

std::unique_ptr<Expression> EndActivityExpressionFactory::generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                                   std::shared_ptr<Scope> &scope) {
    return std::make_unique<EndActivityExpression>();
}
