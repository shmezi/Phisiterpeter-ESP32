//
// Created by Ezra Golombek on 02/11/2025.
//

#ifndef PHISILANDINTERPRETER_SCOPE_H
#define PHISILANDINTERPRETER_SCOPE_H
#include <map>
#include <string>
#include  <memory>

#include "../expressions/BaseExpression.h"
#include "expressions/Expression.h"
#include "factories/Factory.h"
#include "factories/internal/BaseFactory.h"

class BaseExpression; // Forward declaration

class Factory; // Forward declaration

class Scope : public std::enable_shared_from_this<Scope> {
    std::map<std::string, std::shared_ptr<BaseExpression> > variables;
    std::shared_ptr<Scope> parent;

    std::map<std::string, std::shared_ptr<Factory> > keyWords;

public:
    std::string scopeId;


    bool isKeyWord(const std::string &id) const;

    void registerKeyWord(std::shared_ptr<Factory> &&factory);

    template<typename ExpressionType>
    void registerKeyWord();

    std::shared_ptr<Factory> getFactoryById(const std::string &id);

    bool isVariable(const std::string &id) const;

    std::shared_ptr<Scope> getNearestScopeWithVariable(const std::string &id);

    void setVariable(const std::string &id, std::shared_ptr<BaseExpression> expression) {
        variables[id] = std::move(expression);
    }


    std::shared_ptr<BaseExpression> interpretVariable(const std::string &id);


    std::shared_ptr<const Scope> getScopeById(const std::string &id) const;


    Scope(std::string id, std::shared_ptr<Scope> parent) : parent(std::move(parent)), scopeId(std::move(id)) {
    }

    explicit Scope(std::string id) : scopeId(std::move(id)) {
    }

    ~Scope() = default;
};


 void Scope::registerKeyWord(){
    ExpressionInfo info = ExpressionType::getInfo();

    auto names = std::deque<std::string>();
    for (const auto &argument_name: info.argumentNames) {
        names.push_back(argument_name.name);
    }

    const auto dynFactory = std::make_shared<BaseFactory>(info.startToken, names, ExpressionType::generate);
    keyWords[info.startToken] = std::move(dynFactory);
}
#endif //PHISILANDINTERPRETER_SCOPE_H
