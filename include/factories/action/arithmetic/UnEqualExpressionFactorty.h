//
// Created by Ezra Golombek on 30/11/2025.
//

#ifndef PHISILANDINTERPRETER_UNEQUALEXPRESSIONFACTORTY_H
#define PHISILANDINTERPRETER_UNEQUALEXPRESSIONFACTORTY_H
#include "factories/Factory.h"


class UnEqualExpressionFactorty final : public Factory {
public:
    std::string startToken() override;

    int paramSize() override;




    UnEqualExpressionFactorty() = default;

    std::unique_ptr<Expression> generate(std::deque<std::unique_ptr<Expression> > &arguments, std::shared_ptr<Scope> &scope) override;

    int indexStart() override;

    ~UnEqualExpressionFactorty() override = default;
};

#endif //PHISILANDINTERPRETER_UNEQUALEXPRESSIONFACTORTY_H