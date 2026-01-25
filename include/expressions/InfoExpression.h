//
// Created by Ezra Golombek on 25/01/2026.
//

#ifndef PHISITERPETER_ESP32_INFOEXPRESSION_H
#define PHISITERPETER_ESP32_INFOEXPRESSION_H
#include <deque>

#include "Expression.h"

template<typename DerivedExpression>
class InfoExpression : public Expression {
    static std::string startToken() {
        return DerivedExpression::startToken();
    };


    static std::string endToken() {
        return DerivedExpression::endToken();
    };

    static int indexStart() {
        return DerivedExpression::indexStart();
    };

    static int paramSize() {
        return DerivedExpression::paramSize();
    };


    // Not gonna lie, i'm not sure why it's ok that we are passing a variable that gets deleted... maybe its because we generate it and then we dont actually need the stuff after that idk.. Im just getting started with memory management stuff.
    static std::unique_ptr<Expression> generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                std::shared_ptr<Scope> &scope) {
        return DerivedExpression::generate(arguments, &scope);
    }
};
#endif //PHISITERPETER_ESP32_INFOEXPRESSION_H
