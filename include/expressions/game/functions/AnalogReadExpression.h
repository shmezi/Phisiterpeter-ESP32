//
// Created by Ezra Golombek on 26/01/2026.
//

#ifndef PHISITERPETER_ESP32_ANALOGREADEXPRESSION_H
#define PHISITERPETER_ESP32_ANALOGREADEXPRESSION_H
#include "expressions/Expression.h"

#include <esp_adc/adc_oneshot.h>

class AnalogReadExpression : public Expression {
    bool registered = false;
    adc_oneshot_unit_handle_t adc_handle;

public:
    std::unique_ptr<Expression> pin;

    std::string expressionName() override;

    std::shared_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    AnalogReadExpression(std::unique_ptr<Expression> pin);
};


#endif //PHISITERPETER_ESP32_ANALOGREADEXPRESSION_H
