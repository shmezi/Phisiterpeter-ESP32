//
// Created by Ezra Golombek on 26/01/2026.
//


#include "expressions/game/functions/AnalogReadExpression.h"

#include <esp_err.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_adc/adc_oneshot.h>

#include "Utils.h"
#include "expressions/internal/VoidExpression.h"
#include "expressions/value/BooleanExpression.h"
#include "expressions/value/NumberExpression.h"
#define ADC_BITWIDTH  ADC_BITWIDTH_12   // 12-bit resolution (0-4095)
#define ADC_ATTEN     ADC_ATTEN_DB_12   // ~3.3V full-scale voltage

adc_oneshot_chan_cfg_t config = {
    .atten = ADC_ATTEN,
    .bitwidth = ADC_BITWIDTH
};

// Configure ADC channel

adc_oneshot_unit_handle_t AnalogReadExpression::adc_handle_a;

adc_oneshot_unit_handle_t AnalogReadExpression::adc_handle_b;


adc_oneshot_unit_init_cfg_t AnalogReadExpression::init_config_a = {
    .unit_id = ADC_UNIT_1,
    .clk_src = ADC_RTC_CLK_SRC_DEFAULT,
};

adc_oneshot_unit_init_cfg_t AnalogReadExpression::init_config_b = {
    .unit_id = ADC_UNIT_2,
    .clk_src = ADC_RTC_CLK_SRC_DEFAULT,
};


std::string AnalogReadExpression::expressionName() {
    return "analog";
}

std::shared_ptr<Expression> AnalogReadExpression::interpret(std::shared_ptr<Scope> scope) {
    int adc_value;
     adc_oneshot_unit_handle_t unit = adc_handle_a;
    auto pinValue = dynamic_cast<NumberExpression *>(pin->interpret(scope).get())->contents;
    if (pinValue >= 10) {
        pinValue -= 11;
        unit = adc_handle_b;
    }

    auto actualPinNumber = static_cast<adc_channel_t>(pinValue);


    if (!this->registered) {
        ESP_ERROR_CHECK(adc_oneshot_config_channel(unit, actualPinNumber, &config));
        this->registered = true;
    }


    ESP_ERROR_CHECK(adc_oneshot_read(unit, actualPinNumber, &adc_value));

    return std::make_shared<NumberExpression>(adc_value);
}

std::string AnalogReadExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}

AnalogReadExpression::AnalogReadExpression(std::unique_ptr<Expression> pin) {
    this->pin = std::move(pin);
}
