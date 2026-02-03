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
#include "driver/mcpwm.h"
#include "esp_log.h"


#include "driver/gpio.h"
#include "esp_log.h"
#include "base/ScheduleLoop.h"
#include "base/Scope.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void MotorExpression::move(const float speedValue) {
    auto pinA = static_cast<gpio_num_t>(dynamic_cast<NumberExpression *>(a.get())->contents);
    auto pinB = static_cast<gpio_num_t>(dynamic_cast<NumberExpression *>(b.get())->contents);
    auto pinSpeed = static_cast<gpio_num_t>(dynamic_cast<NumberExpression *>(speed.get())->contents);

    debug::print("Running motor at speed of " + std::to_string(speedValue));
    if (!GPIO_IS_VALID_GPIO(pinA) || !GPIO_IS_VALID_GPIO(pinB)) {
        debug::error("Pin is invalid");
    }

    if (speedValue == 0) {
        gpio_set_level(pinA, false);
        gpio_set_level(pinB, false);
    }
    gpio_set_level(pinA, speedValue > 0);
    gpio_set_level(pinB, speedValue < 0);

    if (!run) {

        gpio_set_direction(pinA, GPIO_MODE_OUTPUT);
        gpio_set_direction(pinB, GPIO_MODE_OUTPUT);
        // Init MCPWM with 1 kHz frequency, 50% duty
        mcpwm_config_t pwm_config;
        pwm_config.frequency = 1000; // 1 kHz
        pwm_config.cmpr_a = speedValue; // 50% duty cycle
        pwm_config.cmpr_b = 0.0; // unused
        pwm_config.counter_mode = MCPWM_UP_COUNTER;
        pwm_config.duty_mode = MCPWM_DUTY_MODE_0;


        mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);




        mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, pinSpeed);
        run = true;
    }
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_GEN_A, abs(speedValue));


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

        debug::print("ITEM LOOP");
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
