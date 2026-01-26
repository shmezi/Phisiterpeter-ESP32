//
// Created by Ezra Golombek on 02/11/2025.
//


#include "../../../../include/expressions/action/control/SetExpression.h"

#include <iostream>
#include <ostream>

#include "../../../../include/base/Scope.h"
#include "expressions/internal/VoidExpression.h"

std::shared_ptr<BaseExpression> SetExpression::interpret(std::shared_ptr<Scope> scope) {
    const auto id = std::any_cast<std::string>(this->name->instanceId());
    auto value = this->content->interpret(scope);
    const auto nearScope = scope->getNearestScopeWithVariable(id);
    if (nearScope == nullptr)
        scope->setVariable(id, std::move(value));
    else
        nearScope->setVariable(id, std::move(value));


    return std::make_unique<VoidExpression>();
}


SetExpression::SetExpression(std::unique_ptr<BaseExpression> name, std::unique_ptr<BaseExpression> content) {
    this->name = std::move(name);
    this->content = std::move(content);
}

std::string SetExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "Setting a value :)";
}
