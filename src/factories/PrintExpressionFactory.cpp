//
// Created by Ezra Golombek on 02/11/2025.
//

#include "../../include/factories/PrintExpressionFactory.h"

#include <string>
#include <vector>

#include "../../include/expressions/action/PrintExpression.h"

std::unique_ptr<BaseExpression> PrintExpressionFactory::generate(std::deque<std::unique_ptr<BaseExpression> > &arguments, std::shared_ptr<Scope> &scope) {
    return std::make_unique<PrintExpression>(std::move(arguments[0]));

}

int PrintExpressionFactory::indexStart() {
    return 0;
}

int PrintExpressionFactory::paramSize() {
    return 1;
}

std::string PrintExpressionFactory::startToken() {
    return "print";
}

