//
// Created by Ezra Golombek on 07/11/2025.
//

#include "../../../include/expressions/value/BooleanExpression.h"

#include <string>


std::string BooleanExpression::expressionName() {
    return "booleanExpression";
}

std::shared_ptr<Expression> BooleanExpression::interpret(std::shared_ptr<Scope> scope) {
    return std::make_unique<BooleanExpression>(contents);
}

std::string BooleanExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return this->contents ? "true" : "false";
}

std::string BooleanExpression::instanceId() {
    return "boolean-" + std::string(this->contents ? "true" : "false");
}

std::shared_ptr<Expression> BooleanExpression::notOperator(std::shared_ptr<Scope> &parentScope) {
    return std::make_unique<BooleanExpression>(!contents);
}

std::shared_ptr<Expression> BooleanExpression::orOperator(std::shared_ptr<Expression> &&expression,
                                                          std::shared_ptr<Scope> &parentScope) {
    return std::make_unique<BooleanExpression>(
        dynamic_cast<BooleanExpression *>(expression.get())->contents || contents);
}

std::shared_ptr<Expression> BooleanExpression::andOperator(std::shared_ptr<Expression> &&expression,
                                                           std::shared_ptr<Scope> &parentScope) {
    return std::make_unique<BooleanExpression>(
        dynamic_cast<BooleanExpression *>(expression.get())->contents && contents);
}
