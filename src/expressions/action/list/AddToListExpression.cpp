//
// Created by Ezra Golombek on 07/12/2025.
//

#include "expressions/action/list/AddToListExpression.h"

#include <algorithm>

#include "expressions/internal/VoidExpression.h"
#include "expressions/value/ListExpression.h"

std::string AddToListExpression::expressionName() {
    return "addToList";
}

std::shared_ptr<Expression> AddToListExpression::interpret(std::shared_ptr<Scope> scope) {
    auto actualList = dynamic_cast<ListExpression *>(list->interpret(scope).get());
    actualList->append(newItem->interpret(scope));
    return std::make_shared<VoidExpression>();
}

std::string AddToListExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "Adding " + newItem->interpertAsString(scope) + " to a list";
}

AddToListExpression::AddToListExpression(std::unique_ptr<Expression> list, std::unique_ptr<Expression> newItem)
    : list(std::move(list)), newItem(std::move(newItem)) {
}
