//
// Created by Ezra Golombek on 25/01/2026.
//

#ifndef PHISITERPETER_ESP32_INFOEXPRESSION_H
#define PHISITERPETER_ESP32_INFOEXPRESSION_H
#include <deque>

#include "BaseExpression.h"
#include "base/ExpressionInfo.h"
#include <chrono>
template<typename DerivedExpression>
class Expression : public BaseExpression {
    static ExpressionInfo getInfo() {
        return DerivedExpression::getInfo();
    };

    static std::unique_ptr<BaseExpression> generate(std::deque<std::unique_ptr<BaseExpression> > &arguments,
                                                    std::shared_ptr<Scope> &scope) {
        return DerivedExpression::generate(arguments, &scope);
    }
};
#endif //PHISITERPETER_ESP32_INFOEXPRESSION_H
