//
// Created by Ezra Golombek on 02/11/2025.
//

#include "../../../include/expressions/value/FloatyText.h"

#include <iostream>

#include "../../../include/base/Scope.h"
#include "Utils.h"
#include "expressions/internal/VoidExpression.h"
#include "expressions/value/NumberExpression.h"
#include "logging/Logger.h"

std::shared_ptr<Expression> FloatyText::interpret(std::shared_ptr<Scope> scope) {
    if (!scope->isVariable(actualFloatyText))
    {
        for (unsigned char c : actualFloatyText) {
            printf("%02X ", c);
        }
        printf("\n");
        std::cout <<   "Value " << actualFloatyText << " END" <<std::endl;
        Logger::error(
            "No declaration found token: `" + actualFloatyText + "`" + " at line " + std::to_string(lineNumber));
        return nullptr;
    }


    return (scope->interpretVariable(actualFloatyText));
}

std::string FloatyText::interpretAsString(std::shared_ptr<Scope> scope) {
    if (!scope->isVariable(actualFloatyText)) {


        Logger::error(
            "No declaration found token: `" + actualFloatyText + "`" + " at line " + std::to_string(lineNumber));
        return "";
    }

    return scope->interpretVariable(actualFloatyText)->interpretAsString(scope);
}


std::string FloatyText::instanceId() {
    return actualFloatyText;
}
