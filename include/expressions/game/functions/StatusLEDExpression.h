//
// Created by Ezra Golombek on 01/12/2025.
//

#ifndef PHISITERPETER_ESP32_STATUSLEDEXPRESSION_H
#define PHISITERPETER_ESP32_STATUSLEDEXPRESSION_H
#include "expressions/Expression.h"
#include "managed_components/espressif__led_strip/include/led_strip.h"

class StatusLEDExpression : public Expression {
    std::unique_ptr<Expression> r;
    std::unique_ptr<Expression> g;
    std::unique_ptr<Expression> b;

public:
    static led_strip_config_t strip_config;
    static led_strip_rmt_config_t rmt_config;
    static led_strip_handle_t statusLight;

    std::string expressionName() override;


    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    StatusLEDExpression(std::unique_ptr<Expression> r, std::unique_ptr<Expression> g, std::unique_ptr<Expression> b);
};


#endif //PHISITERPETER_ESP32_STATUSLEDEXPRESSION_H
