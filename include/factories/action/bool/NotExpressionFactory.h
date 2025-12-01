//
// Created by Ezra Golombek on 11/11/2025.
//

#ifndef PHISILANDINTERPRETER_NOTEXPRESSIONFACTORY_H
#define PHISILANDINTERPRETER_NOTEXPRESSIONFACTORY_H
#include "factories/Factory.h"


class NotExpressionFactory : public Factory {
public:


    std::string startToken() override;

    int indexStart() override;

    int paramSize() override;

    std::unique_ptr<Expression> generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                         std::shared_ptr<Scope> &scope) override;
};


#endif //PHISILANDINTERPRETER_NOTEXPRESSIONFACTORY_H
