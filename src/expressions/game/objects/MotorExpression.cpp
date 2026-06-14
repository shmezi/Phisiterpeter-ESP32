//
// Created by Ezra Golombek on 03/12/2025.
//

#include "../../../../include/expressions/game/objects/MotorExpression.h"
#include <esp_intr_alloc.h>
#include <driver/gpio.h>
#include "esp_intr_alloc.h"

#include <algorithm>
#include <stdio.h>
#include "driver/pcnt.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "Utils.h"
#include "driver/gpio.h"
#include "expressions/value/NumberExpression.h"
// #include "driver/mcpwm.h"
#include "esp_log.h"


#include "driver/gpio.h"
#include "esp_log.h"
#include "base/ScheduleLoop.h"
#include "base/Scope.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/mcpwm_prelude.h"
#include "logging/Logger.h"


void MotorExpression::move(const float speedValue) {
    auto pinA = static_cast<gpio_num_t>(dynamic_cast<NumberExpression *>(a.get())->contents);
    auto pinB = static_cast<gpio_num_t>(dynamic_cast<NumberExpression *>(b.get())->contents);
    auto pinSpeed = static_cast<gpio_num_t>(dynamic_cast<NumberExpression *>(speed.get())->contents);


    // ---- Initialize MCPWM once ----
    if (!run) {
        run = true;

        gpio_set_direction(pinA, GPIO_MODE_OUTPUT);
        gpio_set_direction(pinB, GPIO_MODE_OUTPUT);

        mcpwm_timer_config_t timer_config = {};
        timer_config.group_id = 0;
        timer_config.clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT;
        timer_config.resolution_hz = 1000000; // 1 MHz resolution
        timer_config.count_mode = MCPWM_TIMER_COUNT_MODE_UP;
        timer_config.period_ticks = 20000; // 20 kHz PWM
        mcpwm_new_timer(&timer_config, &timer);

        mcpwm_operator_config_t operator_config = {};
        operator_config.group_id = 0;
        mcpwm_new_operator(&operator_config, &oper);

        mcpwm_operator_connect_timer(oper, timer);

        mcpwm_comparator_config_t comparator_config = {};

        comparator_config.flags.update_cmp_on_tez = true;

        mcpwm_new_comparator(oper, &comparator_config, &comparator);

        mcpwm_generator_config_t gen_config = {};
        gen_config.gen_gpio_num = pinSpeed;
        mcpwm_new_generator(oper, &gen_config, &generator);

        mcpwm_generator_set_action_on_timer_event(
            generator,
            MCPWM_GEN_TIMER_EVENT_ACTION(
                MCPWM_TIMER_DIRECTION_UP,
                MCPWM_TIMER_EVENT_EMPTY,
                MCPWM_GEN_ACTION_HIGH));

        mcpwm_generator_set_action_on_compare_event(
            generator,
            MCPWM_GEN_COMPARE_EVENT_ACTION(
                MCPWM_TIMER_DIRECTION_UP,
                comparator,
                MCPWM_GEN_ACTION_LOW));

        mcpwm_timer_enable(timer);
        mcpwm_timer_start_stop(timer, MCPWM_TIMER_START_NO_STOP);
    }

    // ---- Direction control ----
    bool forward = speedValue >= 0;


    if (speedValue == 0) {
        gpio_set_level(pinA, 1);
        gpio_set_level(pinB, 1);
        return;
    }

    float speedAbs = std::min(std::abs(speedValue), 100.0f);

    gpio_set_level(pinA, forward ? 1 : 0);
    gpio_set_level(pinB, forward ? 0 : 1);

    // ---- Set PWM duty ----
    auto duty = static_cast<uint32_t>((speedAbs / 100.0f) * 20000);
    mcpwm_comparator_set_compare_value(comparator, duty);
}

void MotorExpression::stop() {
}

std::string MotorExpression::expressionName() {
    return "motor";
}


std::shared_ptr<Expression> MotorExpression::interpret(std::shared_ptr<Scope> scope) {
    return shared_from_this();
}


std::string MotorExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return std::to_string(rotations);
    // return "A: " + a->interpertAsString(scope) + " B: " + b->interpertAsString(scope) + " Speed: " + speed->
    //        interpertAsString(scope) + " EncoderA: "
    //        + encoderA->interpertAsString(scope) + " EncoderB: " + encoderB->interpertAsString(scope);
}

void MotorExpression::rotate() {
    rotations += (gpio_get_level(bActualPin) == 0) ? -1 : 1;
}

int MotorExpression::getActualRotations() const {
    return rotations / 330;
}


void MotorExpression::rotateUntilRotation(int rotateTo, int speedToRunAt) {
    requestRotation = rotateTo;

    // Determine current position to decide direction
    int currentPos = getActualRotations();
    bool movingForward = (rotateTo > currentPos);

    // Apply speed in the correct direction
    move((movingForward ? -1 : 1) * std::abs(speedToRunAt));

    // Capture the target and direction to monitor progress
    ScheduleLoop::getInstance()->addTask([rotateTo, movingForward, m = shared_from_this()] {
        // If target is already reached or request was cleared (e.g., set to 0 elsewhere)
        if (m->requestRotation == 0) return;

        int current = m->getActualRotations();

        // Stop condition based on direction
        bool reached = movingForward ? (current >= rotateTo) : (current <= rotateTo);

        if (reached) {
            m->move(0);
            m->requestRotation = 0; // Clear the request
        }

        Logger::log("ITEM LOOP: " + std::to_string(current) + " " + std::to_string(rotateTo));
    });
}

// ISR function for the button
extern "C" void IRAM_ATTR gpio_isr_handler(void *arg) {
    auto *expression = static_cast<MotorExpression *>(arg);
    expression->rotate();
}

void MotorExpression::initEncoder() {
    auto encoderAPin = static_cast<gpio_num_t>(dynamic_cast<NumberExpression *>(encoderA.get())->contents);
    auto encoderBPin = static_cast<gpio_num_t>(dynamic_cast<NumberExpression *>(encoderB.get())->contents);

    // debug::print(std::to_string(encoderAPin));
    bActualPin = encoderBPin;
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << encoderAPin),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_NEGEDGE, // Trigger on falling edge (button press)
    };
    gpio_config(&io_conf);


    gpio_isr_handler_add(encoderAPin, gpio_isr_handler, (void *) this);
    gpio_set_direction(encoderBPin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(encoderBPin, GPIO_PULLUP_ONLY);
}


MotorExpression::MotorExpression(std::unique_ptr<Expression> a, std::unique_ptr<Expression> b,
                                 std::unique_ptr<Expression> speed, std::unique_ptr<Expression> encoderA,
                                 std::unique_ptr<Expression> encoderB)
    : a(std::move(a)), b(std::move(b)), speed(std::move(speed)), encoderA(std::move(encoderA)),
      encoderB(std::move(encoderB)) {
    rotations = 0;

    initEncoder();
}
