//
// Created by Ezra Golombek on 02/11/2025.
//

#ifndef PHISILANDINTERPRETER_INTERPRETER_H
#define PHISILANDINTERPRETER_INTERPRETER_H
#include <map>
#include <string>
#include <vector>

#include "ScheduleLoop.h"
#include "../expressions/BaseExpression.h"
#include "Scope.h"
class Token;
class Factory;
using namespace std;

class Interpreter {

    shared_ptr<Scope> headScope;
    vector<Token> tokens;

    void interpretKeyWordExpression(const Token &token);

public:
    vector<unique_ptr<BaseExpression> > abstractSyntaxTree = vector<unique_ptr<BaseExpression> >();

    void registerFactories() const;



    explicit Interpreter(const shared_ptr<Scope> &headScope, const vector<Token> &tokens);

    void run() const;

    void interpret(vector<Token> &tokens, int limit = -1, const string &endToken = " ");

    void interpret(int limit = -1) {
        interpret(tokens, limit);
    };

    void interpret(const string &endToken = " ") {
        interpret(tokens, -1, endToken);
    };
};


#endif //PHISILANDINTERPRETER_INTERPRETER_H
