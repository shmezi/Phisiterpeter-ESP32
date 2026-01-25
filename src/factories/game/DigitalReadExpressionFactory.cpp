//
// Created by Ezra Golombek on 02/12/2025.
//

#include "../../../include/factories/game/functions/DigitalReadExpressionFactory.h"

#include "../../../include/expressions/game/functions/DigitalReadExpression.h"

std::string DigitalReadExpressionFactory::startToken() {
    return "read";
}

int DigitalReadExpressionFactory::indexStart() {
    return 0;
}

int DigitalReadExpressionFactory::paramSize() {
    return 1;
}

std::unique_ptr<Expression> DigitalReadExpressionFactory::generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                                   std::shared_ptr<Scope> &scope) {
    return std::make_unique<DigitalReadExpression>(std::move(arguments[0]));
}
