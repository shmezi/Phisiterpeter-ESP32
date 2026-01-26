//
// Created by Ezra Golombek on 07/12/2025.
//

#ifndef PHISITERPETER_ESP32_LISTEXPRESSION_H
#define PHISITERPETER_ESP32_LISTEXPRESSION_H
#include <deque>

#include "expressions/BaseExpression.h"


class ListExpression : public BaseExpression, public std::enable_shared_from_this<ListExpression> {
    std::deque<std::shared_ptr<BaseExpression> > items = std::deque<std::shared_ptr<BaseExpression> >();

public:
    std::string expressionName() override;

    std::shared_ptr<BaseExpression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    void clear();

    void append(std::shared_ptr<BaseExpression> item);

    explicit ListExpression(std::deque<std::shared_ptr<BaseExpression> > items);
};


#endif //PHISITERPETER_ESP32_LISTEXPRESSION_H
