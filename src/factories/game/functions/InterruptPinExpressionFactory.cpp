//
// Created by Ezra Golombek on 16/03/2026.
//

#include "../../../../include/factories/game/functions/InterruptPinExpressionFactory.h"

#include "expressions/action/control/ValueHoldExpression.h"
#include "expressions/game/functions/InterruptPinExpression.h"

std::string InterruptPinExpressionFactory::startToken() {
    return "reactOn";
}

int InterruptPinExpressionFactory::indexStart() {
    return 0;
}

int InterruptPinExpressionFactory::paramSize() {
    return 2;
}

std::unique_ptr<Expression> InterruptPinExpressionFactory::generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                                    std::shared_ptr<Scope> &scope) {
    return std::make_unique<ValueHoldExpression>(
        std::make_shared<InterruptPinExpression>(

            std::move(arguments[0]),
            std::move(arguments[1]))
    );

}
