//
// Created by Ezra Golombek on 13/03/2026.
//
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/mcpwm_prelude.h"

#include "../../../../include/expressions/game/functions/ServoExpression.h"

#include "Utils.h"
#include "expressions/internal/VoidExpression.h"
#include "expressions/value/NumberExpression.h"

// Static storage for the generator handle (mapped to the pin)
static mcpwm_gen_handle_t generator = nullptr;

std::set<int> ServoExpression::registeredPins;

ServoExpression::ServoExpression(std::unique_ptr<Expression> pinNumber, std::unique_ptr<Expression> value)
    : pinNumber(std::move(pinNumber)), value(std::move(value)) {
}

std::string ServoExpression::expressionName() {
    return "servo";
}

mcpwm_cmpr_handle_t comparator = nullptr;

void registerPin(int pin) {
    // 1. Setup Timer
    mcpwm_timer_handle_t timer = nullptr;
    mcpwm_timer_config_t timer_config = {};
    timer_config.group_id = 0; // Try group 0 first
    timer_config.clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT;
    timer_config.resolution_hz = 1000000;
    timer_config.count_mode = MCPWM_TIMER_COUNT_MODE_UP;
    timer_config.period_ticks = 20000;
    ESP_ERROR_CHECK(mcpwm_new_timer(&timer_config, &timer));

    // 2. Setup Operator
    mcpwm_oper_handle_t oper = nullptr;
    mcpwm_operator_config_t oper_config = {};
    oper_config.group_id = 0;
    ESP_ERROR_CHECK(mcpwm_new_operator(&oper_config, &oper));
    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(oper, timer));

    // 3. Setup Comparator
    mcpwm_comparator_config_t cmpr_config = {};
    cmpr_config.flags.update_cmp_on_tez = true;
    ESP_ERROR_CHECK(mcpwm_new_comparator(oper, &cmpr_config, &comparator));

    // 4. Setup Generator
    mcpwm_generator_config_t gen_config = {.gen_gpio_num = pin};
    ESP_ERROR_CHECK(mcpwm_new_generator(oper, &gen_config, &generator));

    // 5. SET ACTIONS (This is where the waveform is born)
    // Go HIGH when timer is 0
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(generator,
        MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));

    // Go LOW when timer matches comparator
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(generator,
        MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, comparator, MCPWM_GEN_ACTION_LOW)));

    // 6. Start
    ESP_ERROR_CHECK(mcpwm_timer_enable(timer));
    ESP_ERROR_CHECK(mcpwm_timer_start_stop(timer, MCPWM_TIMER_START_NO_STOP));
}

std::shared_ptr<Expression> ServoExpression::interpret(std::shared_ptr<Scope> scope) {
    const auto evaluatedPin = (dynamic_cast<NumberExpression *>(pinNumber->interpret(scope).get()))->contents;
    auto evaluatedValue = (dynamic_cast<NumberExpression *>(value->interpret(scope).get()))->contents;

    // 1. Clamp the value between 0 and 180 (degrees)
    if (evaluatedValue < 0) evaluatedValue = 0;
    if (evaluatedValue > 180) evaluatedValue = 180;

    if (!registeredPins.contains(evaluatedPin)) {
        registerPin(evaluatedPin);
        registeredPins.insert(evaluatedPin);
    }

    // 2. Map Degrees to Microseconds
    // Formula: pulse = min + (angle / max_angle) * (max_pulse - min_pulse)
    // 500us (0deg) to 2500us (180deg)
    uint32_t servo_ticks = 500 + static_cast<uint32_t>(evaluatedValue * 2000 / 180);

    mcpwm_comparator_set_compare_value(comparator, servo_ticks);

    return std::make_shared<VoidExpression>();
}
