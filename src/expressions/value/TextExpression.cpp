//
// Created by Ezra Golombek on 02/11/2025.
//

#include "../../../include/expressions/value/TextExpression.h"


#include "../../../include/base/Scope.h"
#include "expressions/internal/VoidExpression.h"

std::shared_ptr<Expression> TextExpression::interpret(std::shared_ptr<Scope> scope) {
    return std::make_unique<TextExpression>(contents);
}

std::string TextExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return contents;
}

std::shared_ptr<Expression> TextExpression::addition(std::shared_ptr<Expression> &&expression,
                                                     std::shared_ptr<Scope> &parentScope) {
    return make_unique<TextExpression>(this->contents + expression->interpertAsString(parentScope));
}
