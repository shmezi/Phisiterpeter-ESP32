//
// Created by Ezra Golombek on 16/03/2026.
//

#include "../../../../include/expressions/game/functions/InterruptPinExpression.h"

#include <esp_attr.h>
#include <esp_timer.h>
#include <driver/gpio.h>

#include "Utils.h"
#include "../../../../include/base/dovetail/DovetailCore.h"
#include "base/ScheduleLoop.h"
#include "base/Scope.h"
#include "expressions/internal/VoidExpression.h"
#include "expressions/value/NumberExpression.h"

std::string InterruptPinExpression::expressionName() {
    return "reactOn";
}

struct ISRArgs {
    InterruptPinExpression *obj;
    int id;
    std::shared_ptr<Scope> scope;
};

void InterruptPinExpression::trampoline(int id) {
    ScheduleLoop::getInstance()->queueIDTask(id, esp_timer_get_time());
}

void IRAM_ATTR handleGlobalInterrupt(void *arg) {
    const auto obj = static_cast<ISRArgs *>(arg);
    obj->obj->trampoline(obj->id);
}

std::shared_ptr<Expression> InterruptPinExpression::interpret(std::shared_ptr<Scope> scope) {
    if (!registered) {
        auto evaluatedPin = static_cast<gpio_num_t>(dynamic_cast<NumberExpression *>(pin->interpret(scope).get())->
            contents);
        Logger::log("Registering interrupt pin on pin: " + std::to_string(evaluatedPin));
        registered = true;
        gpio_config_t io_conf = {
            .pin_bit_mask = (1ULL << evaluatedPin),
            .mode = GPIO_MODE_INPUT,
            .pull_up_en = GPIO_PULLUP_ENABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type = GPIO_INTR_NEGEDGE, // Trigger on falling edge (button press)
        };
        gpio_config(&io_conf);


        taskID = ScheduleLoop::getInstance()->newIDTask(codeBlock, scope);
        auto *args = new ISRArgs{this, taskID, scope};
        gpio_isr_handler_add(evaluatedPin, handleGlobalInterrupt, (void *) args);
        Logger::log("Registered task id: " + std::to_string(taskID));
    }
    return shared_from_this();
}
