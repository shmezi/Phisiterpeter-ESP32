//
// Created by Ezra Golombek on 03/02/2026.
//

#include "../../../../include/factories/game/functions/Wrap360ExpressionFactory.h"

#include "expressions/game/functions/Wrap360Expression.h"

std::string Wrap360ExpressionFactory::startToken() {
    return "wrap360";
}

int Wrap360ExpressionFactory::indexStart() {
    return 0;
}

int Wrap360ExpressionFactory::paramSize() {
    return 1;
}

std::unique_ptr<Expression> Wrap360ExpressionFactory::generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                               std::shared_ptr<Scope> &scope) {
    return std::make_unique<Wrap360Expression>(std::move(arguments[0]));
}
