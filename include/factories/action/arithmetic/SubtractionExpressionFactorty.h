//
// Created by Ezra Golombek on 30/11/2025.
//

#ifndef PHISILANDINTERPRETER_SUBTRACTIONEXPRESSIONFACTORTY_H
#define PHISILANDINTERPRETER_SUBTRACTIONEXPRESSIONFACTORTY_H
#include "factories/Factory.h"


class SubtractionExpressionFactorty final : public Factory {
public:
    std::string startToken() override;

    int paramSize() override;




    SubtractionExpressionFactorty() = default;

    std::unique_ptr<Expression> generate(std::deque<std::unique_ptr<Expression> > &arguments, std::shared_ptr<Scope> &scope) override;

    int indexStart() override;

    ~SubtractionExpressionFactorty() override = default;
};


#endif //PHISILANDINTERPRETER_SUBTRACTIONEXPRESSIONFACTORTY_H