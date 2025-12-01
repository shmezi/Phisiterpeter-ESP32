//
// Created by Ezra Golombek on 07/11/2025.
//

#include "../../../include/expressions/value/BooleanExpression.h"

#include <string>


std::string BooleanExpression::expressionName() {
    return "booleanExpression";
}

std::unique_ptr<Expression> BooleanExpression::interpret(std::shared_ptr<Scope> scope) {
    return std::make_unique<BooleanExpression>(contents);
}

std::string BooleanExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return std::to_string(contents);
}

std::string BooleanExpression::instanceId() {
    return "boolean-" + std::string(this->contents ? "true" : "false");
}

std::unique_ptr<Expression> BooleanExpression::notOperator(std::shared_ptr<Scope> &parentScope) {
    return std::make_unique<BooleanExpression>(!contents);
}

std::unique_ptr<Expression> BooleanExpression::orOperator(std::unique_ptr<Expression> &&expression,
                                                           std::shared_ptr<Scope> &parentScope) {
    return std::make_unique<BooleanExpression>(dynamic_cast<BooleanExpression*>(expression.get())->contents || contents);
}

std::unique_ptr<Expression> BooleanExpression::andOperator(std::unique_ptr<Expression> &&expression,
                                                          std::shared_ptr<Scope> &parentScope) {
    return std::make_unique<BooleanExpression>(dynamic_cast<BooleanExpression*>(expression.get())->contents && contents);
}
