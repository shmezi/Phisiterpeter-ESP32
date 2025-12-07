//
// Created by Ezra Golombek on 02/11/2025.
//

#ifndef PHISILANDINTERPRETER_SCOPE_H
#define PHISILANDINTERPRETER_SCOPE_H
#include <map>
#include <string>
#include  <memory>

#include "../expressions/Expression.h"
#include "factories/Factory.h"
class Expression; // Forward declaration

class Factory; // Forward declaration

class Scope : public std::enable_shared_from_this<Scope> {
    std::map<std::string, std::shared_ptr<Expression> > variables;
    std::shared_ptr<Scope> parent;

    std::map<std::string, std::shared_ptr<Factory> > keyWords;

public:
    std::string scopeId;


    bool isKeyWord(const std::string &id) const;

    void registerKeyWord(std::shared_ptr<Factory> &&factory);

    std::shared_ptr<Factory> getFactoryById(const std::string &id);

    bool isVariable(const std::string &id) const;

    void setVariable(const std::string &id, std::shared_ptr<Expression> expression) {
        variables[id] = std::move(expression);
    }


    std::shared_ptr<Expression> interpretVariable(const std::string &id);


    std::shared_ptr<const Scope> getScopeById(const std::string &id) const;


    Scope(std::string id, std::shared_ptr<Scope> parent) : parent(std::move(parent)), scopeId(std::move(id)) {
    }

    explicit Scope(std::string id) : scopeId(std::move(id)) {
    }

    ~Scope() = default;
};


#endif //PHISILANDINTERPRETER_SCOPE_H
