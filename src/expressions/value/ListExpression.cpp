//
// Created by Ezra Golombek on 07/12/2025.
//

#include "expressions/value/ListExpression.h"

#include <algorithm>

#include "Utils.h"

std::string ListExpression::expressionName() {
    return "list";
}

std::shared_ptr<BaseExpression> ListExpression::interpret(std::shared_ptr<Scope> scope) {
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

void ListExpression::clear() {
    items.clear();
}

void ListExpression::append(std::shared_ptr<BaseExpression> item) {
    items.emplace_back(std::move(item));
}

ListExpression::ListExpression(std::deque<std::shared_ptr<BaseExpression> > items) : items(std::move(items)) {
    debug::print("Created a list with " + std::to_string(this->items.size()) + " items.");
}
