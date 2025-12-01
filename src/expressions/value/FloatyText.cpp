//
// Created by Ezra Golombek on 02/11/2025.
//

#include "../../../include/expressions/value/FloatyText.h"

#include <iostream>

#include "../../../include/base/Scope.h"
#include "Utils.h"
#include "expressions/value/NumberExpression.h"

std::unique_ptr<Expression> FloatyText::interpret(std::shared_ptr<Scope> scope) {
    if (!scope->isVariable(actualFloatyText))
    {
        debug::error(
            "No declaration found token: `" + actualFloatyText + "`" + " at line " + std::to_string(lineNumber));
    }


    return (scope->interpretVariable(actualFloatyText));
}

std::string FloatyText::interpertAsString(std::shared_ptr<Scope> scope) {
    if (!scope->isVariable(actualFloatyText)) {
        debug::error(
            "No declaration found token: `" + actualFloatyText + "`" + " at line " + std::to_string(lineNumber));
        return "";
    }

    return scope->interpretVariable(actualFloatyText)->interpertAsString(scope);
}


std::string FloatyText::instanceId() {
    return actualFloatyText;
}
