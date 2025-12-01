//
// Created by Ezra Golombek on 30/10/2025.
//

#ifndef PHISILANDINTERPRETER_NUMBEREXPRESSIONFACTORY_H
#define PHISILANDINTERPRETER_NUMBEREXPRESSIONFACTORY_H
#include "../../Factory.h"
#include "../../../expressions/value/NumberExpression.h"


class AdditionExpressionFactory final : public Factory {
public:
    std::string startToken() override;

    int paramSize() override;




    AdditionExpressionFactory() = default;

    std::unique_ptr<Expression> generate(std::deque<std::unique_ptr<Expression> > &arguments, std::shared_ptr<Scope> &scope) override;

    int indexStart() override;

    ~AdditionExpressionFactory() override = default;
};


#endif //PHISILANDINTERPRETER_NUMBEREXPRESSIONFACTORY_H
