//
// Created by Ezra Golombek on 01/12/2025.
//

#include "expressions/game/StatusLEDExpression.h"

#include <esp_err.h>
#include <soc/clk_tree_defs.h>

#include "expressions/internal/VoidExpression.h"
#include "expressions/value/NumberExpression.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "Utils.h"
#include <stdio.h>

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <SmartLeds.h>
#include <thread>


std::string StatusLEDExpression::expressionName() {
    return "statusLED";
}

static SmartLed leds(LED_WS2812B, 1, 48, 0, DoubleBuffer);

std::shared_ptr<Expression> StatusLEDExpression::interpret(std::shared_ptr<Scope> scope) {
    unsigned char rLED = dynamic_cast<NumberExpression *>(r.get())->contents;
    unsigned char gLED = dynamic_cast<NumberExpression *>(g.get())->contents;
    unsigned char bLED = dynamic_cast<NumberExpression *>(b.get())->contents;


    leds[0] = Rgb{rLED, gLED, bLED};
    leds.show();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    return std::make_unique<VoidExpression>();
}

std::string StatusLEDExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "";
}

StatusLEDExpression::StatusLEDExpression(std::unique_ptr<Expression> r, std::unique_ptr<Expression> g,
                                         std::unique_ptr<Expression> b) : r(std::move(r)), g(std::move(g)),
                                                                          b(std::move(b)) {
}
