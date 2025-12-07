//
// Created by Ezra Golombek on 08/11/2025.
//

#include "expressions/action/control/IfExpression.h"

#include <string>

#include "Utils.h"
#include "base/Scope.h"
#include "expressions/internal/VoidExpression.h"
#include "expressions/value/BooleanExpression.h"

std::string IfExpression::expressionName() {
    return "if";
}

std::shared_ptr<Expression> IfExpression::interpret(std::shared_ptr<Scope> scope) {
    if (this->check->interpret(scope)->expressionName() != "booleanExpression") {
        debug::error("If expression expected a boolean value but got a " + this->check->interpret(scope)->expressionName() + "! on line: " + std::to_string(this->lineNumber));
        return std::make_unique<VoidExpression>();
    }
    const auto isTrue = dynamic_cast<BooleanExpression *>(this->check->interpret(scope).get())->contents;
    if (isTrue) {
        auto result = this->codeBlock->interpret(std::make_shared<Scope>("ifScope", scope));
        return result;
    }
    return std::make_unique<VoidExpression>();
}

std::string IfExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "For some reason we are printing an If stat?!";
}

IfExpression::IfExpression(std::unique_ptr<Expression> check, std::unique_ptr<Expression> codeBlock) {
    this->check = std::move(check);
    this->codeBlock = std::move(codeBlock);
}
