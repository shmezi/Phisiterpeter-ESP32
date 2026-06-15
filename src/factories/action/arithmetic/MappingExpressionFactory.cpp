//
// Created by Ezra Golombek on 14/06/2026.
//

#include "factories/action/arithmetic/MappingExpressionFactory.h"

#include "expressions/action/arithmetic/MappingExpression.h"
#include "expressions/value/NumberExpression.h"


//Example usage: 10 50 mapped 400 1000
std::string MappingExpressionFactory::startToken() {
    return "mapped";
}

int MappingExpressionFactory::indexStart() {
    return -1;
}

int MappingExpressionFactory::paramSize() {
    return 5;
}

std::unique_ptr<Expression> MappingExpressionFactory::generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                               std::shared_ptr<Scope> &scope) {
    return std::make_unique<MappingExpression>(std::move(arguments[0]), std::move(arguments[1]), std::move(arguments[2]),
                                               std::move(arguments[3]), std::move(arguments[4]));
}
