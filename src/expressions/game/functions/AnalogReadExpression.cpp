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

std::string AnalogReadExpression::expressionName() {
    return "analog";
}

std::shared_ptr<Expression> AnalogReadExpression::interpret(std::shared_ptr<Scope> scope) {
    int adc_value;
    adc_unit_t unit = ADC_UNIT_1;
    auto pinValue = dynamic_cast<NumberExpression *>(pin->interpret(scope).get())->contents;
    if (pinValue >= 10) {
        pinValue -= 11;
        unit = ADC_UNIT_2;
    }

    auto actualPinNumber = static_cast<adc_channel_t>(pinValue);


    if (!this->registered) {
        // Initialize ADC Oneshot Mode Driver on the ADC Unit
        adc_oneshot_unit_init_cfg_t init_config = {
            .unit_id = unit,
            .clk_src = ADC_RTC_CLK_SRC_DEFAULT,
        };
        ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc_handle));

        // Configure ADC channel
        adc_oneshot_chan_cfg_t config = {
            .atten = ADC_ATTEN,
            .bitwidth = ADC_BITWIDTH
        };
        ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, actualPinNumber, &config));
        this->registered = true;
    }


    ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, actualPinNumber, &adc_value));

    return std::make_shared<NumberExpression>(adc_value);
}

std::string AnalogReadExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}

AnalogReadExpression::AnalogReadExpression(std::unique_ptr<Expression> pin) {
    this->pin = std::move(pin);
}
