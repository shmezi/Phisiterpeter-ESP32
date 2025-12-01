//
// Created by Ezra Golombek on 30/11/2025.
//

#ifndef PHISILANDINTERPRETER_EQUALSEXPRESSIONFACTORTY_H
#define PHISILANDINTERPRETER_EQUALSEXPRESSIONFACTORTY_H
#include "factories/Factory.h"



class EqualsExpressionFactory final : public Factory {
public:
    std::string startToken() override;

    int paramSize() override;




    EqualsExpressionFactory() = default;

    std::unique_ptr<Expression> generate(std::deque<std::unique_ptr<Expression> > &arguments, std::shared_ptr<Scope> &scope) override;

    int indexStart() override;

    ~EqualsExpressionFactory() override = default;
};


#endif //PHISILANDINTERPRETER_EQUALSEXPRESSIONFACTORTY_H