//
// Created by Ezra Golombek on 16/03/2026.
//

#include "../../../../include/expressions/game/functions/InterruptPinExpression.h"

#include <esp_attr.h>
#include <driver/gpio.h>

#include "Utils.h"
#include "base/DovetailCore.h"
#include "base/ScheduleLoop.h"
#include "expressions/internal/VoidExpression.h"
#include "expressions/value/NumberExpression.h"

std::string InterruptPinExpression::expressionName() {
    return "reactOn";
}


void InterruptPinExpression::trampoline() {
    ScheduleLoop::getInstance()->queueIDTask(taskID);
}

void IRAM_ATTR handleGlobalInterrupt(void *arg) {
    static_cast<InterruptPinExpression *>(arg)->trampoline();
}

std::shared_ptr<Expression> InterruptPinExpression::interpret(std::shared_ptr<Scope> scope) {
    if (!registered) {
        auto evaluatedPin = static_cast<gpio_num_t>(dynamic_cast<NumberExpression *>(pin->interpret(scope).get())->
            contents);
        debug::log("Registering interupt pin on pin: " + std::to_string(evaluatedPin));
        registered = true;
        gpio_config_t io_conf = {
            .pin_bit_mask = (1ULL << evaluatedPin),
            .mode = GPIO_MODE_INPUT,
            .pull_up_en = GPIO_PULLUP_ENABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type = GPIO_INTR_NEGEDGE, // Trigger on falling edge (button press)
        };
        gpio_config(&io_conf);
        // gpio_isr_handler_add(evaluatedPin, handleGlobalInterrupt, (void *) this);

        taskID = ScheduleLoop::getInstance()->newIDTask([cb = codeBlock,scope] {
            cb->interpret(scope);
        });
    }
    return shared_from_this();
}
