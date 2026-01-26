//
// Created by Ezra Golombek on 02/11/2025.
//


#include "../../../../include/factories/action/control/SetExpressionFactory.h"

#include <iostream>
#include <string>
#include <vector>

#include "../../../../include/base/Scope.h"
#include "../../../../include/expressions/action/control/SetExpression.h"

int SetExpressionFactory::indexStart() {
    return -1;
}

int SetExpressionFactory::paramSize() {
    return 2;
}

std::string SetExpressionFactory::startToken() {
    return "=";
}


std::unique_ptr<BaseExpression> SetExpressionFactory::generate(std::deque<std::unique_ptr<BaseExpression> > &arguments, std::shared_ptr<Scope> &scope) {

    return std::make_unique<SetExpression>(std::move(arguments[0]), std::move(arguments[1]));

}
