//
// Created by Ezra Golombek on 04/11/2025.
//

#ifndef PHISILANDINTERPRETER_CLARIFICATIONBRACKETEXPRESSIONFACTORY_H
#define PHISILANDINTERPRETER_CLARIFICATIONBRACKETEXPRESSIONFACTORY_H
#include <vector>

#include "../../Factory.h"
#include "../../../expressions/action/control/ClarificationBracketExpression.h"


class ClarificationBracketExpressionFactory : public Factory {

public:
    ~ClarificationBracketExpressionFactory() override = default;

    std::string startToken() override;

    std::string endToken() override;

    int indexStart() override;

    int paramSize() override;





    std::unique_ptr<Expression> generate(std::deque<std::unique_ptr<Expression> > &arguments, std::shared_ptr<Scope> &scope) override;

};


#endif //PHISILANDINTERPRETER_CLARIFICATIONBRACKETEXPRESSIONFACTORY_H
