//
// Created by Ezra Golombek on 02/11/2025.
//

#include "../../../include/expressions/value/FloatyText.h"

#include <iostream>

#include "../../../include/base/Scope.h"
#include "Utils.h"
#include "expressions/internal/VoidExpression.h"
#include "expressions/value/NumberExpression.h"

std::shared_ptr<BaseExpression> FloatyText::interpret(std::shared_ptr<Scope> scope) {
    if (!scope->isVariable(actualFloatyText))
    {
        for (unsigned char c : actualFloatyText) {
            printf("%02X ", c);
        }
        printf("\n");
        std::cout <<   "Value " << actualFloatyText << " END" <<std::endl;
        debug::error(
            "No declaration found token: `" + actualFloatyText + "`" + " at line " + std::to_string(lineNumber));
        return nullptr;
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
