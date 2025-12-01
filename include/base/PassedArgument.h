//
// Created by Ezra Golombek on 06/11/2025.
//

#ifndef PHISILANDINTERPRETER_PASSEDARGUMENT_H
#define PHISILANDINTERPRETER_PASSEDARGUMENT_H
#include <string>


class PassedArgument {
public:
    std::unique_ptr<Expression> argument;
    std::string name;
    PassedArgument(std::unique_ptr<Expression> argument, std::string name) : argument(std::move(argument)), name(std::move(name)) {}
};


#endif //PHISILANDINTERPRETER_PASSEDARGUMENT_H