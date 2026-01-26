//
// Created by Ezra Golombek on 30/11/2025.
//

#ifndef PHISILANDINTERPRETER_LESSEREXPRESSIONFACTORTY_H
#define PHISILANDINTERPRETER_LESSEREXPRESSIONFACTORTY_H
#include "factories/Factory.h"


class LesserExpressionFactorty final : public Factory {
public:
    std::string startToken() override;

    int paramSize() override;


    LesserExpressionFactorty() = default;

    std::unique_ptr<BaseExpression> generate(std::deque<std::unique_ptr<BaseExpression> > &arguments,
                                         std::shared_ptr<Scope> &scope) override;

    int indexStart() override;

    ~LesserExpressionFactorty() override = default;
};

#endif //PHISILANDINTERPRETER_LESSEREXPRESSIONFACTORTY_H
