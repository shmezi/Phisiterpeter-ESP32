//
// Created by Ezra Golombek on 01/12/2025.
//

#include "../../../../include/expressions/game/functions/StatusLEDExpression.h"

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
#include <thread>


std::string StatusLEDExpression::expressionName() {
    return "statusLED";
}

led_strip_config_t StatusLEDExpression::strip_config = {
    .strip_gpio_num = 48, // The GPIO that connected to the LED strip's data line
    .max_leds = 1, // The number of LEDs in the strip,
    .led_model = LED_MODEL_WS2812, // LED strip model, it determines the bit timing
    .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB, // The color component format is G-R-B
    .flags = {
        .invert_out = false, // don't invert the output signal
    }
};
led_strip_rmt_config_t StatusLEDExpression::rmt_config = {
    .clk_src = RMT_CLK_SRC_DEFAULT, // different clock source can lead to different power consumption
    .resolution_hz = 10 * 1000 * 1000, // RMT counter clock frequency: 10MHz
    .mem_block_symbols = 64, // the memory size of each RMT channel, in words (4 bytes)
    .flags = {
        .with_dma = false, // DMA feature is available on chips like ESP32-S3/P4
    }
};
led_strip_handle_t StatusLEDExpression::statusLight = nullptr;

std::shared_ptr<Expression> StatusLEDExpression::interpret(std::shared_ptr<Scope> scope) {
    unsigned char rLED = static_cast<char>(dynamic_cast<NumberExpression *>(r.get())->contents);
    unsigned char gLED = static_cast<char>(dynamic_cast<NumberExpression *>(g.get())->contents);
    unsigned char bLED = static_cast<char>(dynamic_cast<NumberExpression *>(b.get())->contents);


    // leds[0] = Rgb{rLED, gLED, bLED};
    // leds.show();
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));

    return std::make_unique<VoidExpression>();
}

std::string StatusLEDExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "";
}

StatusLEDExpression::StatusLEDExpression(std::unique_ptr<Expression> r, std::unique_ptr<Expression> g,
                                         std::unique_ptr<Expression> b) : r(std::move(r)), g(std::move(g)),
                                                                          b(std::move(b)) {
}
