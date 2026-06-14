//
// Created by Ezra Golombek on 12/06/2026.
//

#include "../../../include/factories/dovetail/RemoteLogExpressionFactory.h"

#include "expressions/dovetail/RemoteLogExpression.h"

std::string RemoteLogExpressionFactory::startToken() {
    return "remoteLog";
}

int RemoteLogExpressionFactory::indexStart() {
    return 0;
}

int RemoteLogExpressionFactory::paramSize() {
    return 1;
}

std::unique_ptr<Expression> RemoteLogExpressionFactory::generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                                 std::shared_ptr<Scope> &scope) {
    return std::make_unique<RemoteLogExpression>(std::move(arguments[0]));
}
