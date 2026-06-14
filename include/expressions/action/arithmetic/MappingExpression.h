//
// Created by Ezra Golombek on 14/06/2026.
//

#ifndef PHISITERPETER_ESP32_MAPPINGEXPRESSION_H
#define PHISITERPETER_ESP32_MAPPINGEXPRESSION_H



#include "expressions/Expression.h"
#include <memory>

class MappingExpression : public Expression {
public:
    MappingExpression(
        std::unique_ptr<Expression> value,
        std::unique_ptr<Expression> inputMin,
        std::unique_ptr<Expression> inputMax,
        std::unique_ptr<Expression> outputMin,
        std::unique_ptr<Expression> outputMax
    );

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;
    std::string interpretAsString(std::shared_ptr<Scope> scope) override;

private:
    std::unique_ptr<Expression> value;
    std::unique_ptr<Expression> inputMin;
    std::unique_ptr<Expression> inputMax;
    std::unique_ptr<Expression> outputMin;
    std::unique_ptr<Expression> outputMax;
};


#endif //PHISITERPETER_ESP32_MAPPINGEXPRESSION_H
