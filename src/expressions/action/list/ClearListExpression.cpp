//
// Created by Ezra Golombek on 07/12/2025.
//

#include "expressions/action/list/ClearListExpression.h"

#include "Utils.h"
#include "expressions/internal/VoidExpression.h"
#include "expressions/value/ListExpression.h"

std::string ClearListExpression::expressionName() {
    return "clearList";
}

std::shared_ptr<Expression> ClearListExpression::interpret(std::shared_ptr<Scope> scope) {
    dynamic_cast<ListExpression *>(list->interpret(scope).get())->clear();
    return std::make_shared<VoidExpression>();
}

std::string ClearListExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "clearing list";
}

ClearListExpression::ClearListExpression(std::unique_ptr<Expression> list) : list(std::move(list)) {
}
