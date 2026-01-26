//
// Created by Ezra Golombek on 30/11/2025.
//

#ifndef PHISILANDINTERPRETER_MULTIPICATIONEXPRESSIONFACTORTY_H
#define PHISILANDINTERPRETER_MULTIPICATIONEXPRESSIONFACTORTY_H
#include "factories/Factory.h"


class MultiplicationExpressionFactorty final : public Factory {
public:
    std::string startToken() override;

    int paramSize() override;




    MultiplicationExpressionFactorty() = default;

    std::unique_ptr<BaseExpression> generate(std::deque<std::unique_ptr<BaseExpression> > &arguments, std::shared_ptr<Scope> &scope) override;

    int indexStart() override;

    ~MultiplicationExpressionFactorty() override = default;
};

#endif //PHISILANDINTERPRETER_MULTIPICATIONEXPRESSIONFACTORTY_H