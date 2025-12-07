//
// Created by Ezra Golombek on 02/12/2025.
//
#include <string>

#include "Utils.h"
#include "base/Scope.h"
#include "expressions/internal/VoidExpression.h"
#include "expressions/value/BooleanExpression.h"

#include "../../../../include/expressions/action/control/WhileExpression.h"
//
// Created by Ezra Golombek on 08/11/2025.
//


std::string WhileExpression::expressionName() {
    return "while";
}

std::shared_ptr<Expression> WhileExpression::interpret(std::shared_ptr<Scope> scope) {
    if (this->check->interpret(scope)->expressionName() != "booleanExpression") {
        debug::error(
            "While expression expected a boolean value but got a " + this->check->interpret(scope)->expressionName() +
            "! on line: " + std::to_string(this->lineNumber));
        return std::make_unique<VoidExpression>();
    }
    const auto whileScope = std::make_shared<Scope>("ifScope", scope);

    while (dynamic_cast<BooleanExpression *>(this->check->interpret(scope).get())->contents) {
        codeBlock->interpret(whileScope);
    }
    return std::make_unique<VoidExpression>();
}

std::string WhileExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "For some reason we are printing an If stat?!";
}

WhileExpression::WhileExpression(std::unique_ptr<Expression> check, std::unique_ptr<Expression> codeBlock) {
    this->check = std::move(check);
    this->codeBlock = std::move(codeBlock);
}
