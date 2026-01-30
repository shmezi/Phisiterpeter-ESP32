//
// Created by Ezra Golombek on 29/10/2025.
//

#ifndef PHISILANDINTERPRETER_FACTORY_H
#define PHISILANDINTERPRETER_FACTORY_H
#include <any>
#include <deque>
#include <string>
#include <memory>
class Scope;
class Expression;

/**
 * user = (expressions_here) => {
 *
 * }
 * Let's break this down to it's core expressions:
 *
 * user - a Floaty text.
 * = - a Set Statement.
 * ( - Start of a clarification statement. -> Since it DOES have an end of expression token, it calls interpert saying wait for the end token which is )
 * expressions_here - Floaty text -> All expressions are appended to the calrification statement.
 * => - Function statement -> Takes 1 lookbehind and one lookahead stat to a codeblock
 * { - Start of a codeblock statement. -> Calls interpert function saying wait for the end token which is }
 *
 *
 *
 *
 *
 *
 */
class Factory {
public:
    virtual ~Factory() = default;

    virtual std::string startToken() = 0;


    virtual std::string endToken() {
        return " ";
    };

    virtual int indexStart() = 0;

    virtual int paramSize() = 0;

    virtual bool doesSplit() {
        return false;
    };



    // Not gonna lie, i'm not sure why it's ok that we are passing a variable that gets deleted... maybe its because we generate it and then we dont actually need the stuff after that idk.. Im just getting started with memory management stuff.
    virtual std::unique_ptr<Expression> generate(std::deque<std::unique_ptr<Expression> > &arguments,
                                                 std::shared_ptr<Scope> &scope) = 0;
};

#endif //PHISILANDINTERPRETER_FACTORY_H
