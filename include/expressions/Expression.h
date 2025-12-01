//
// Created by Ezra Golombek on 30/10/2025.
//

#ifndef PHISILANDINTERPRETER_EXPRESSION_H
#define PHISILANDINTERPRETER_EXPRESSION_H
#include <any>
#include <memory>
#include <string>

class Scope;
/*
 * An expression expresses our entire program. Our program is built up of many expressions connected together that are then run
 */
class Expression {
public:
    virtual ~Expression() = default;

    int lineNumber = 0;

    virtual std::unique_ptr<Expression> copy() {
        return nullptr;
    }

    /**
     * The name of the expression, global to all instances of the expression.
     * @return Name of the expression (Internal identifier for expression type)
     */
    virtual std::string expressionName() = 0;

    /**
    * This instance of the expression's ID. This may be duplicate, this is entirely expression dependant.
    * @return Id of the expression
    */

    virtual std::string instanceId() {
        return expressionName();
    };


    virtual std::unique_ptr<Expression> equal(std::unique_ptr<Expression> &&expression,
                                              std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }

    virtual std::unique_ptr<Expression> unequal(std::unique_ptr<Expression> &&expression,
                                                std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }

    virtual std::unique_ptr<Expression> greater(std::unique_ptr<Expression> &&expression,
                                                std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }

    virtual std::unique_ptr<Expression> lesser(std::unique_ptr<Expression> &&expression,
                                               std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }


    virtual std::unique_ptr<Expression>
    addition(std::unique_ptr<Expression> &&expression,
             std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }

    virtual std::unique_ptr<Expression> division(std::unique_ptr<Expression> &&expression,
                                                 std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }

    virtual std::unique_ptr<Expression> multiply(std::unique_ptr<Expression> &&expression,
                                                 std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }

    virtual std::unique_ptr<Expression> subtract(std::unique_ptr<Expression> &&expression,
                                                 std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }

    virtual std::unique_ptr<Expression> notOperator(std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }

    virtual std::unique_ptr<Expression> andOperator(std::unique_ptr<Expression> &&expression,
                                                    std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }

    virtual std::unique_ptr<Expression> orOperator(std::unique_ptr<Expression> &&expression,
                                                   std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }

    virtual std::unique_ptr<Expression> toOperator(std::unique_ptr<Expression> &&expression,
                                                   std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }


    virtual std::unique_ptr<Expression> indexOperator(std::any &index, std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }


    virtual std::unique_ptr<Expression> interpret(std::shared_ptr<Scope> scope) = 0;


    virtual std::string interpertAsString(std::shared_ptr<Scope> scope) = 0;
};

#endif //PHISILANDINTERPRETER_EXPRESSION_H
