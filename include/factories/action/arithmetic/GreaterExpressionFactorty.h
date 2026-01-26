//
// Created by Ezra Golombek on 30/11/2025.
//

#ifndef PHISILANDINTERPRETER_GREATEREXPRESSIONFACTORTY_H
#define PHISILANDINTERPRETER_GREATEREXPRESSIONFACTORTY_H
#include "factories/Factory.h"


class GreaterExpressionFactorty final : public Factory {
public:
    std::string startToken() override;

    int paramSize() override;




    GreaterExpressionFactorty() = default;

    std::unique_ptr<BaseExpression> generate(std::deque<std::unique_ptr<BaseExpression> > &arguments, std::shared_ptr<Scope> &scope) override;

    int indexStart() override;

    ~GreaterExpressionFactorty() override = default;
};

#endif //PHISILANDINTERPRETER_GREATEREXPRESSIONFACTORTY_H