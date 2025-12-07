//
// Created by Ezra Golombek on 07/12/2025.
//

#ifndef PHISITERPETER_ESP32_LISTEXPRESSION_H
#define PHISITERPETER_ESP32_LISTEXPRESSION_H
#include <deque>

#include "expressions/Expression.h"


class ListExpression : public Expression, public std::enable_shared_from_this<ListExpression> {
    std::deque<std::shared_ptr<Expression> > items = std::deque<std::shared_ptr<Expression> >();

public:
    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    void clear();

    void append(std::shared_ptr<Expression> item);

    ListExpression(std::deque<std::shared_ptr<Expression> > items);
};


#endif //PHISITERPETER_ESP32_LISTEXPRESSION_H
