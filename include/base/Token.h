//
// Created by Ezra Golombek on 02/11/2025.
//

#ifndef PHISILANDINTERPRETER_TOKEN_H
#define PHISILANDINTERPRETER_TOKEN_H
#include <string>

#include "base/TokenType.h"

class Token {
public:
    std::string tokenId;
    int lineNumber;
    enum TokenType type;

    Token(std::string startId, enum TokenType type, int lineCount) : tokenId(std::move(startId)),

                                                                     lineNumber(lineCount), type(type) {
    };
};


#endif //PHISILANDINTERPRETER_TOKEN_H
