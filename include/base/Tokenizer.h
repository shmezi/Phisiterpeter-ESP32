//
// Created by Ezra Golombek on 30/11/2025.
//

#ifndef PHISILANDINTERPRETER_TOKENIZER_H
#define PHISILANDINTERPRETER_TOKENIZER_H
#include <string>
#include <utility>
#include <vector>

#include "Scope.h"
#include "Token.h"


class Tokenizer {
    char currentlyParsedChar = ' ';
    std::string currentToken;
    int lineCount = 1;
    FILE &stream;
    std::shared_ptr<Scope> headScope;

public:
    std::vector<Token> tokens = std::vector<Token>();

    void pushNewTokenToList(char streamingChar);

    void tokenize();

    Tokenizer(FILE &stream, std::shared_ptr<Scope> headScope);

};


#endif //PHISILANDINTERPRETER_TOKENIZER_H
