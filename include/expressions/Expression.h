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

    /**
     * Line inside the scripting language
     */
    int lineNumber = 0;

    /**
     * Clones the expression giving a new copy of it.
     * ( Unless an expression is marked as a reference object, all objects are copied.
     * @return Returns an exact copy of the expression.
     */
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

    /**
     * Equality check between two expressions. (Used for the internal `==` Expression
     * @param expression Expression to compare this object to
     * @param parentScope The parent scope that will be used for interpretation of the expressions.
     * @return
     */
    virtual std::shared_ptr<Expression> equal(std::shared_ptr<Expression> &&expression,
                                              std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }

    virtual std::shared_ptr<Expression> unequal(std::shared_ptr<Expression> &&expression,
                                                std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }

    virtual std::shared_ptr<Expression> greater(std::shared_ptr<Expression> &&expression,
                                                std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }

    virtual std::shared_ptr<Expression> lesser(std::shared_ptr<Expression> &&expression,
                                               std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }


    virtual std::shared_ptr<Expression>
    addition(std::shared_ptr<Expression> &&expression,
             std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }

    virtual std::shared_ptr<Expression> division(std::shared_ptr<Expression> &&expression,
                                                 std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }

    virtual std::shared_ptr<Expression> multiply(std::shared_ptr<Expression> &&expression,
                                                 std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }

    virtual std::shared_ptr<Expression> subtract(std::shared_ptr<Expression> &&expression,
                                                 std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }

    virtual std::shared_ptr<Expression> notOperator(std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }

    virtual std::shared_ptr<Expression> andOperator(std::shared_ptr<Expression> &&expression,
                                                    std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }

    virtual std::shared_ptr<Expression> orOperator(std::shared_ptr<Expression> &&expression,
                                                   std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }

    virtual std::shared_ptr<Expression> toOperator(std::shared_ptr<Expression> &&expression,
                                                   std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }

    virtual std::shared_ptr<Expression> modifier(std::string &keyword, std::shared_ptr<Scope> &parentScopescope) {
        return nullptr;
    };

    virtual std::shared_ptr<Expression> indexOperator(std::any &index, std::shared_ptr<Scope> &parentScope) {
        return nullptr;
    }


    virtual std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) = 0;


    virtual std::string interpertAsString(std::shared_ptr<Scope> scope) {
        return interpret(scope)->interpertAsString(scope);
    };
};

#endif //PHISILANDINTERPRETER_EXPRESSION_H
