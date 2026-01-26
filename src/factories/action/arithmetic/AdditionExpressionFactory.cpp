//
// Created by Ezra Golombek on 30/10/2025.
//

#include "../../../../include/factories/action/arithmetic/AdditionExpressionFactory.h"

#include <iostream>
#include <string>
#include <vector>

#include "../../../../include/expressions/action/arithmetic/AdditionExpression.h"

std::unique_ptr<BaseExpression> AdditionExpressionFactory::generate(std::deque<std::unique_ptr<BaseExpression> > &arguments, std::shared_ptr<Scope> &scope) {

    return std::make_unique<AdditionExpression>(std::move(arguments[0]), std::move(arguments[1]));
}


int AdditionExpressionFactory::paramSize() {
    return 2;
}

std::string AdditionExpressionFactory::startToken() {
    return "+";
}

int AdditionExpressionFactory::indexStart() {
    return -1;
}
