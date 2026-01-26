//
// Created by Ezra Golombek on 26/01/2026.
//

#include "../../../include/factories/internal/BaseFactory.h"


std::string BaseFactory::startToken() {
    return passStartToken;
}

int BaseFactory::indexStart() {
    return passIndexStart;
}

int BaseFactory::paramSize() {
    return passParamSize;
}

std::string BaseFactory::endToken() {
    return passEndToken;
}

std::unique_ptr<BaseExpression> BaseFactory::generate(
    std::deque<std::unique_ptr<BaseExpression> > &arguments,
    std::shared_ptr<Scope> &scope) {
    return this->passGenerator(std::move(arguments),scope);
}
