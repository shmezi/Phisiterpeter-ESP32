//
// Created by Ezra Golombek on 29/11/2025.
//

#ifndef PHISILANDINTERPRETER_NODECLERATIONEXCEPSSION_H
#define PHISILANDINTERPRETER_NODECLERATIONEXCEPSSION_H
#include "ExceptionExpression.h"

class NoDeclarationException  : public ExceptionExpression {
public:
    explicit NoDeclarationException(std::string error) : ExceptionExpression(
        "NoDeclarationException", std::move(error)) {
    }
    ~NoDeclarationException() override = default;

};

#endif //PHISILANDINTERPRETER_NODECLERATIONEXCEPSSION_H
