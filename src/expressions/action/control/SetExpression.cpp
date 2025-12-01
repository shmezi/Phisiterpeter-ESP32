//
// Created by Ezra Golombek on 02/11/2025.
//


#include "../../../../include/expressions/action/control/SetExpression.h"

#include <iostream>
#include <ostream>

#include "../../../../include/base/Scope.h"
#include "expressions/internal/VoidExpression.h"

std::unique_ptr<Expression> SetExpression::interpret(std::shared_ptr<Scope> scope) {
    const auto id = std::any_cast<std::string>(this->name->instanceId());
    auto value = this->content->interpret(scope);
    scope->setVariable(id, std::move(value));

    return std::make_unique<VoidExpression>();
}


SetExpression::SetExpression(std::unique_ptr<Expression> name, std::unique_ptr<Expression> content) {
    this->name = std::move(name);
    this->content = std::move(content);
}

std::string SetExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "Setting a value :)";
}
