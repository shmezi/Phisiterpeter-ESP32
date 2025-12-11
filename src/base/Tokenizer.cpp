//
// Created by Ezra Golombek on 30/11/2025.
//

#include "base/Tokenizer.h"

#include <iostream>

#include "Utils.h"
#include "base/TokenType.h"
#include <fstream>

#include "../../../../.platformio/packages/toolchain-riscv32-esp/riscv32-esp-elf/include/c++/14.2.0/regex"
#include "base/Scope.h"
std::regex pattern("^\\d+(\\.\\d+)?$");

void Tokenizer::pushNewTokenToList(const char streamingChar = ' ') {

    if (currentToken.empty())
        return;

    enum TokenType type = UNKNOWN;
    if (std::regex_match(currentToken, pattern)) {
        type = NUMBER;
    }
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
bool isBad(char32_t cp) {
    return cp == 0x0D ||        // CR
           cp == 0x202A || cp == 0x202B || cp == 0x202D ||
           cp == 0x202E || cp == 0x202C ||
           cp == 0x200E || cp == 0x200F; // bidi marks
}
void Tokenizer::tokenize() {
    char streamingChar = ' ';
    int c;
    bool hasBadChar = false;
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
        if (isBad(c)) {
            hasBadChar = true;
            continue;
        }


        switch (currentlyParsedChar) {
            case '"':
                pushNewTokenToList();
                streamingChar = currentlyParsedChar;
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '=':
            case '>':
            case '<':
            case '(':
            case ')':
            case '{':
            case '}':
                pushNewTokenToList();
                currentToken += currentlyParsedChar;
                pushNewTokenToList();
                break;
            case '#':
                pushNewTokenToList();
                streamingChar = '#';
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
    if (hasBadChar) {
        debug::warn("You have included a bad character in your file! Please make sure to use a proper text editor!");
    }
}

Tokenizer::Tokenizer(FILE &stream, std::shared_ptr<Scope> headScope) : stream(stream),
                                                                       headScope(std::move(headScope)) {
    // if (!stream.is_open()) {
    //     std::cerr << "Error: Unable to open file." << std::endl;
    // }
}
