//
// Created by Ezra Golombek on 30/11/2025.
//

#include "base/Tokenizer.h"

#include <iostream>

#include "Utils.h"
#include "base/TokenType.h"
#include <fstream>

#include "base/Scope.h"

void Tokenizer::pushNewTokenToList(const char streamingChar = ' ') {
    if (currentToken.empty())
        return;

    enum TokenType type = UNKNOWN;
    if (is_number(currentToken))
        type = NUMBER;
    if (headScope->isKeyWord(currentToken))
        type = KEYWORD;
    if (currentToken == "yes" || currentToken == "no" || currentToken == "true" || currentToken == "false")
        type = BOOL;

    switch (streamingChar) {
        case '"':
            type = TEXT;
            break;
        case '<':
        case '>':
            type = COMMENT;
            break;
        default:
            break;
    }

    tokens.emplace_back(currentToken, type, lineCount);

    currentToken.clear();
};

void Tokenizer::tokenize() {
    char streamingChar = ' ';
    int c;

    while (((c = fgetc(&stream)) != EOF)) {
        currentlyParsedChar = static_cast<char>(c);
        if (streamingChar != ' ') {
            if (currentlyParsedChar == '\n') {
                lineCount++;
            }
            if (currentlyParsedChar == streamingChar) {
                //Make sure the end was recieved :)
                pushNewTokenToList(currentlyParsedChar);
                streamingChar = ' ';
                continue;
            }
            currentToken += currentlyParsedChar;
            continue;
        }

        switch (currentlyParsedChar) {
            case '"':
                pushNewTokenToList();
                streamingChar = currentlyParsedChar;
                break;
            case '+':
            case '=':
            case '(':
            case ')':
            case '{':
            case '}':
                pushNewTokenToList();
                currentToken += currentlyParsedChar;
                pushNewTokenToList();
                break;
            case '<':
                pushNewTokenToList();
                streamingChar = '>';
                break;
            case ' ':
            case ',':
                pushNewTokenToList();
                break;
            case '\n':
                pushNewTokenToList();
                lineCount++;
                break;
            default:
                currentToken += currentlyParsedChar;
                break;
        }
    }
    pushNewTokenToList(); //Push final token to tokens.
}

Tokenizer::Tokenizer(FILE &stream, std::shared_ptr<Scope> headScope) : stream(stream),
                                                                       headScope(std::move(headScope)) {
    // if (!stream.is_open()) {
    //     std::cerr << "Error: Unable to open file." << std::endl;
    // }
}
