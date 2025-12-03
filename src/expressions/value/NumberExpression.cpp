//
// Created by Ezra Golombek on 30/10/2025.
//

#include "expressions/value/NumberExpression.h"

#include <string>

#include "Utils.h"
#include "expressions/value/BooleanExpression.h"
#include "expressions/value/IntRangeExpression.h"


NumberExpression::NumberExpression(const int contents)
    : contents(contents) {
}

std::unique_ptr<Expression> NumberExpression::interpret(std::shared_ptr<Scope> scope) {
    return std::move(std::make_unique<NumberExpression>(contents));
}

std::string NumberExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return std::to_string(contents);
}

std::unique_ptr<Expression> NumberExpression::addition(std::unique_ptr<Expression> &&expression,
                                                       std::shared_ptr<Scope> &parentScope) {
    auto result = expression->interpret(parentScope);
    auto number = dynamic_cast<NumberExpression *>(result.get());
    return std::make_unique<NumberExpression>(number->contents + contents);
}

std::unique_ptr<Expression> NumberExpression::equal(std::unique_ptr<Expression> &&expression,
                                                    std::shared_ptr<Scope> &parentScope) {
    if (expression->expressionName() != "number") {
        return std::make_unique<BooleanExpression>(false);
    }
    auto number = dynamic_cast<NumberExpression *>(expression.get());
    return std::make_unique<BooleanExpression>(number->contents == contents);
}

std::unique_ptr<Expression> NumberExpression::unequal(std::unique_ptr<Expression> &&expression,
                                                      std::shared_ptr<Scope> &parentScope) {
    auto number = dynamic_cast<NumberExpression *>(expression.get());
    return std::make_unique<BooleanExpression>(number->contents != contents);
}

std::unique_ptr<Expression> NumberExpression::greater(std::unique_ptr<Expression> &&expression,
                                                      std::shared_ptr<Scope> &parentScope) {
    auto number = dynamic_cast<NumberExpression *>(expression.get());
    return std::make_unique<BooleanExpression>(contents > number->contents);
}

std::unique_ptr<Expression> NumberExpression::lesser(std::unique_ptr<Expression> &&expression,
                                                     std::shared_ptr<Scope> &parentScope) {
    auto number = dynamic_cast<NumberExpression *>(expression.get());
    return std::make_unique<BooleanExpression>(contents < number->contents);
}

std::unique_ptr<Expression> NumberExpression::division(std::unique_ptr<Expression> &&expression,
                                                       std::shared_ptr<Scope> &parentScope) {
    auto number = dynamic_cast<NumberExpression *>(expression.get());
    return std::make_unique<NumberExpression>(contents / number->contents);
}

std::unique_ptr<Expression> NumberExpression::multiply(std::unique_ptr<Expression> &&expression,
                                                       std::shared_ptr<Scope> &parentScope) {
    auto number = dynamic_cast<NumberExpression *>(expression.get());
    return std::make_unique<NumberExpression>(contents * number->contents);
}

std::unique_ptr<Expression> NumberExpression::subtract(std::unique_ptr<Expression> &&expression,
                                                       std::shared_ptr<Scope> &parentScope) {
    auto number = dynamic_cast<NumberExpression *>(expression.get());
    return std::make_unique<NumberExpression>(contents - number->contents);
}

std::unique_ptr<Expression> NumberExpression::toOperator(std::unique_ptr<Expression> &&expression,
                                                         std::shared_ptr<Scope> &parentScope) {
    auto number = dynamic_cast<NumberExpression *>(expression.get());
    return std::make_unique<IntRangeExpression>(contents, number->contents);
}
