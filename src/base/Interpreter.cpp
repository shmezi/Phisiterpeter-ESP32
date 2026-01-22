//
// Created by Ezra Golombek on 02/11/2025.
//

#include "../../include/base/Interpreter.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>

#include "../../include/expressions/value/BooleanExpression.h"
#include "../../include/factories/action/arithmetic/AdditionExpressionFactory.h"
#include "../../include/factories/Factory.h"
#include "../../include/expressions/value/FloatyText.h"
#include "../../include/expressions/value/TextExpression.h"
#include "../../include/base/TokenType.h"
#include "Utils.h"
#include "../../include/expressions/action/control/ClarificationBracketExpression.h"
#include "expressions/internal/StartExpression.h"
#include "../../include/factories/action/control/ClarificationBracketExpressionFactory.h"
#include "../../include/factories/action/control/FunctionExpressionFactory.h"
#include "factories/PrintExpressionFactory.h"
#include "../../include/factories/action/control/ReturnExpressionFactory.h"
#include "base/ScheduleLoop.h"
#include "base/Token.h"
#include "base/Tokenizer.h"
#include "expressions/game/StatusLEDExpression.h"
#include "factories/action/arithmetic/DivisionExpressionFactorty.h"
#include "factories/action/arithmetic/EqualsExpressionFactory.h"
#include "factories/action/arithmetic/GreaterExpressionFactorty.h"
#include "factories/action/arithmetic/LesserExpressionFactorty.h"
#include "factories/action/arithmetic/MultiplicationExpressionFactorty.h"
#include "factories/action/arithmetic/SubtractionExpressionFactorty.h"
#include "factories/action/arithmetic/UnEqualExpressionFactorty.h"
#include "factories/action/control/CodeblockExpressionFactory.h"
#include "factories/action/control/IfExpressionFactory.h"
#include "factories/action/control/SetExpressionFactory.h"
#include "factories/action/bool/AndExpressionFactory.h"
#include "factories/action/bool/OrExpressionFactory.h"
#include "factories/action/bool/NotExpressionFactory.h"
#include "factories/action/control/WhenExpressionFactory.h"
#include "factories/action/control/WhileExpressionFactory.h"
#include "factories/game/DigitalReadExpressionFactory.h"
#include "factories/game/StatusLEDExpressionFactory.h"
#include "../../include/factories/action/control/RangeOperatorExpressionFactory.h"
#include "expressions/game/ClearCountExpression.h"
#include "expressions/game/CurrentTimeExpression.h"
#include "factories/action/list/AddToListExpressionFactory.h"
#include "factories/action/list/ClearListExpressionFactory.h"
#include "factories/game/AngleExpressionFactory.h"
#include "factories/game/ClearCountExpressionFactory.h"
#include "factories/game/CurrentTimeExpressionFactory.h"
#include "factories/game/GyroScopeExpressionFactory.h"
#include "factories/game/MotorExpressionFactory.h"
#include "factories/game/MoveExpressionFactory.h"
#include "factories/game/OnEventExpressionFactory.h"
#include "factories/game/RotationsExpressionFactory.h"
#include "factories/game/SendResultExpressionFactory.h"
#include "factories/game/SetScreenExpressionFactory.h"
#include "factories/game/WriteExpressionFactory.h"
#include "factories/value/ListExpressionFactory.h"

using namespace std;

void Interpreter::registerFactories() const {
    //Utility factories
    headScope->registerKeyWord(make_unique<PrintExpressionFactory>());
    headScope->registerKeyWord(make_unique<CurrentTimeExpressionFactory>());

    //Codeblock factories
    headScope->registerKeyWord(make_unique<SetExpressionFactory>());
    headScope->registerKeyWord(make_unique<ClarificationBracketExpressionFactory>());
    headScope->registerKeyWord(make_unique<CodeblockExpressionFactory>());
    headScope->registerKeyWord(make_unique<ReturnExpressionFactory>());
    headScope->registerKeyWord(make_unique<FunctionExpressionFactory>());

    //Control statement factories
    headScope->registerKeyWord(make_unique<IfExpressionFactory>());
    headScope->registerKeyWord(make_unique<AndExpressionFactory>());
    headScope->registerKeyWord(make_unique<OrExpressionFactory>());
    headScope->registerKeyWord(make_unique<NotExpressionFactory>());
    headScope->registerKeyWord(make_unique<WhileExpressionFactory>());
    headScope->registerKeyWord(make_unique<WhenExpressionFactory>());
    headScope->registerKeyWord(make_unique<RangeOperatorExpressionFactory>());


    //Math factories
    headScope->registerKeyWord(make_shared<AdditionExpressionFactory>());
    headScope->registerKeyWord(make_unique<SubtractionExpressionFactorty>());
    headScope->registerKeyWord(make_unique<DivisionExpressionFactorty>());
    headScope->registerKeyWord(make_unique<MultiplicationExpressionFactorty>());

    //Equality factories
    headScope->registerKeyWord(make_unique<EqualsExpressionFactory>());
    headScope->registerKeyWord(make_unique<UnEqualExpressionFactorty>());
    headScope->registerKeyWord(make_unique<LesserExpressionFactorty>());
    headScope->registerKeyWord(make_unique<GreaterExpressionFactorty>());


    //Game factories
    headScope->registerKeyWord(make_unique<StatusLEDExpressionFactory>());
    headScope->registerKeyWord(make_unique<DigitalReadExpressionFactory>());
    headScope->registerKeyWord(make_unique<MoveExpressionFactory>());
    headScope->registerKeyWord(make_unique<MotorExpressionFactory>());
    headScope->registerKeyWord(make_unique<WriteExpressionFactory>());
    headScope->registerKeyWord(make_unique<GyroScopeExpressionFactory>());
    headScope->registerKeyWord(make_unique<AngleExpressionFactory>());
    headScope->registerKeyWord(make_unique<RotationsExpressionFactory>());
    headScope->registerKeyWord(make_unique<SendResultExpressionFactory>());
    headScope->registerKeyWord(make_unique<ClearCountExpressionFactory>());
    headScope->registerKeyWord(make_unique<OnEventExpressionFactory>());
    headScope->registerKeyWord(make_unique<SetScreenExpressionFactory>());


    //Lists
    headScope->registerKeyWord(make_unique<ListExpressionFactory>());
    headScope->registerKeyWord(make_unique<ClearListExpressionFactory>());
    headScope->registerKeyWord(make_unique<AddToListExpressionFactory>());
}


Interpreter::Interpreter(const shared_ptr<Scope> &headScope, const vector<Token> &tokens) : headScope(headScope),
    tokens(tokens) {
    registerFactories();


    interpret(-1);
}

void Interpreter::run() const {
    for (const auto &expression: abstractSyntaxTree) {
        expression->interpret(headScope);
        // try {
        //     expression->interpret(headScope);
        // } catch (std::bad_any_cast &e) {
        //     debug::error(
        //         "Anycast Bad arguments provided for expression: `" + expression->expressionName() + "`" +
        //         " Provided: at line: " + std::to_string(expression->lineNumber));
        // } catch (std::exception &e) {
        //     debug::error(
        //         "General Bad arguments provided for expression: `" + expression->expressionName() + "`" +
        //         " Provided: at line: " + std::to_string(expression->lineNumber));
        // }
    }
}

void Interpreter::interpretKeyWordExpression(const Token &token) {
    const auto originalExpressionCount = abstractSyntaxTree.size();
    const auto tokenFactory = headScope->getFactoryById(token.tokenId).get();
    const bool doesLookAhead = abs(tokenFactory->indexStart()) < tokenFactory->paramSize();
    auto expressionsForFactory = vector<unique_ptr<Expression> >();


    if (doesLookAhead || tokenFactory->endToken() != " ") {
        //We could modify the lookahead function to allow for specified end tokens.
        // paramSize: 2 indexStart: -1 = 1 look ahead
        interpret(
            (tokenFactory->paramSize() + tokenFactory->indexStart() + static_cast<int>(abstractSyntaxTree.size())));
        //Limit set to the current number of expressions + amount of paramaters
        //Ex: 1 + 2 4 = 2 expressions. So it is limited to
    }
    if (tokenFactory->endToken() != " ") {
        abstractSyntaxTree.emplace_back(make_unique<StartExpression>());

        interpret(tokenFactory->endToken());

        //Here we must return an expression containing all the obtained expressions.
    }
    if (originalExpressionCount - abstractSyntaxTree.size() < tokenFactory->paramSize()) {
        debug::error(
            "Not enough arguments found for expression `" + token.tokenId + "` Expected: " +
            std::to_string(tokenFactory->paramSize()) + " Found: " + std::to_string(
                originalExpressionCount - abstractSyntaxTree.size()));
        return;
    }

    auto factoryExpressions = deque<unique_ptr<Expression> >();


    for (int i = 0; i < tokenFactory->paramSize(); ++i) {
        //Might be issue just look here if issue and minus one to param size
        factoryExpressions.emplace_front(std::move(abstractSyntaxTree.back()));
        abstractSyntaxTree.pop_back();
    }
    if (tokenFactory->endToken() != " ") {
        while (abstractSyntaxTree.back()->expressionName() != "ise") {
            //Might be issue just look here if issue and minus one to param size
            factoryExpressions.emplace_front(std::move(abstractSyntaxTree.back()));
            abstractSyntaxTree.pop_back();
        }
        abstractSyntaxTree.pop_back();
    }

    if (auto finalExpression = tokenFactory->generate(factoryExpressions, headScope);
        finalExpression->expressionName() != "ide") {
        finalExpression->lineNumber = token.lineNumber;

        abstractSyntaxTree.push_back(std::move(finalExpression));
    }
}


void Interpreter::interpret(vector<Token> &tokens, int limit, const string &endToken) {
    while (!tokens.empty()) {
        const auto token = tokens.front();

        if (limit != -1 && abstractSyntaxTree.size() >= limit)
            break;
        if (endToken != " " && token.tokenId == endToken) {
            tokens.erase(tokens.begin());
            break;
        }
        tokens.erase(tokens.begin());
        auto a = token.tokenId.c_str();
        auto c = ";rocecess ;";
        switch (token.type) {
            case NUMBER: {
                float f = std::stof(token.tokenId);
                auto c = std::make_unique<NumberExpression>(f);
                c->lineNumber = token.lineNumber;
                abstractSyntaxTree.push_back(std::move(c));

                break;
            }
            case KEYWORD:
                //SPEACIAL CASE
                interpretKeyWordExpression(token);
                break;
            case TEXT: {
                auto c = std::make_unique<TextExpression>(token.tokenId);
                c->lineNumber = token.lineNumber;
                abstractSyntaxTree.push_back(std::move(c));
                break;
            }
            case COMMENT:
                break;
            case BOOL: {
                auto c = std::make_unique<BooleanExpression>(token.tokenId == "true" || token.tokenId == "yes");
                c->lineNumber = token.lineNumber;
                abstractSyntaxTree.push_back(std::move(c));
                break;
            }

            // case CLARIFYER:
            // expressions.push_back(std::make_unique<>())
            default: {
                if (headScope->isKeyWord(token.tokenId)) {
                    interpretKeyWordExpression(token); //
                    break;
                }
                auto c = make_unique<FloatyText>(token.tokenId);
                c->lineNumber = token.lineNumber;
                abstractSyntaxTree.push_back(std::move(c));
                break;
            }
        }
    }
}
