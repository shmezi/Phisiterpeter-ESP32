//
// Created by Ezra Golombek on 30/11/2025.
//

#ifndef PHISILANDINTERPRETER_DIVISIONEXPRESSIONFACTORTY_H
#define PHISILANDINTERPRETER_DIVISIONEXPRESSIONFACTORTY_H
#include "factories/Factory.h"


class DivisionExpressionFactorty final : public Factory {
public:
    std::string startToken() override;

    int paramSize() override;




    DivisionExpressionFactorty() = default;

    std::unique_ptr<Expression> generate(std::deque<std::unique_ptr<Expression> > &arguments, std::shared_ptr<Scope> &scope) override;

    int indexStart() override;

    ~DivisionExpressionFactorty() override = default;
};



#endif //PHISILANDINTERPRETER_DIVISIONEXPRESSIONFACTORTY_H