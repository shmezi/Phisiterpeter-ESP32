//
// Created by Ezra Golombek on 07/12/2025.
//

#include "expressions/value/ListExpression.h"

#include <algorithm>

std::string ListExpression::expressionName() {
    return "list";
}

std::shared_ptr<Expression> ListExpression::interpret(std::shared_ptr<Scope> scope) {
    return shared_from_this();
}

std::string ListExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    std::string value = "[";
    bool first = true;
    for (auto &item: items) {
        if (!first) {
            value += ", ";
        }
        value += item.get()->interpertAsString(scope);
        first = false;
    }
    value += "]";
    return value;
}

ListExpression::ListExpression(std::deque<std::unique_ptr<Expression> > items) : items(std::move(items)) {
}
