#include "base/Scope.h"

#include "Utils.h"

bool Scope::isKeyWord(const std::string &id) const { return keyWords.contains(id); }

void Scope::registerKeyWord(std::shared_ptr<Factory> &&factory) {
    keyWords[factory->startToken()] = std::move(factory);
}

std::shared_ptr<Factory> Scope::getFactoryById(const std::string &id) {
    if (keyWords.contains(id))
        return keyWords[id];
    debug::error("Unknown ExpressionFactory of id '" + id + "' Are you sure it's registered?");
    return nullptr;
}

std::shared_ptr<Expression> Scope::interpretVariable(const std::string &id) {
    if (variables.contains(id))

        return variables[id]->interpret(shared_from_this());
    if (parent != nullptr) {
        return parent->interpretVariable(id);
    }
    return nullptr;
}

bool Scope::isVariable(const std::string &id) const {
    if (variables.contains(id))
        return true;
    if (parent != nullptr) {
        return parent->isVariable(id);
    }
    return variables.contains(id);
}

std::shared_ptr<Scope> Scope::getNearestScopeWithVariable(const std::string &id) {
    if (variables.contains(id))
        return shared_from_this();
    if (parent != nullptr) {
        return parent->getNearestScopeWithVariable(id);
    }
    return nullptr;
}

//
// Created by Ezra Golombek on 30/11/2025.
//
std::shared_ptr<const Scope> Scope::getScopeById(const std::string &id) const {
    if (scopeId == id || parent == nullptr) {
        return this->shared_from_this();
    }
    if (parent->scopeId == id) return parent;
    return parent->getScopeById(id);
}
