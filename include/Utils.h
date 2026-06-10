// //
// // Created by Ezra Golombek on 02/11/2025.
// //
//
#ifndef PHISILANDINTERPRETER_UTILS_H
// debug_print.hpp
#pragma once
#include <iostream>
#include <string>
#include <random>
#include "freertos/FreeRTOS.h"

#include "../../../.platformio/packages/toolchain-riscv32-esp/riscv32-esp-elf/include/c++/14.2.0/chrono"
#include "expressions/game/functions/StatusLEDExpression.h"

namespace debug {
    inline double wrap360(const double angle) {
        double result = std::fmod(angle, 360.0);
        if (result < 0) result += 360.0;
        return result;
    }

    enum class Color {
        RED = 31,
        BLUE = 34,
        GREEN = 32,
        PURPLE = 35,
        CYAN = 36,
        YELLOW = 33,
    };


    /*
     * Indicates the current status of the interperter that can be used for status indicators.
     */
    struct RGB {
        unsigned char red;
        unsigned char green;
        unsigned char blue;
    };

    // General Lifecycle
    static constexpr RGB STARTUP = {
        .red = 255, .green = 255, .blue = 255 // White: Neutral starting point
    };
    static constexpr RGB WIFI_SUCCESS = {
        .red = 0, .green = 255, .blue = 255 // Cyan: Connection established
    };
    static constexpr RGB SEARCHING_NETWORK = {
        .red = 150, .green = 150, .blue = 150 // Dim Grey/Pulsing: Idle/Searching
    };
    static constexpr RGB JOINED_NETWORK = {
        .red = 0, .green = 128, .blue = 255 // Azure: Stable link
    };
    static constexpr RGB CODE_LOADED = {
        .red = 255, .green = 0, .blue = 255 // Magenta: Ready to process
    };

    // Processing Pipeline
    static constexpr RGB TOKENIZATION = {
        .red = 0, .green = 0, .blue = 255 // Blue: Logic structure
    };
    static constexpr RGB INTERPRETATION = {
        .red = 102, .green = 0, .blue = 204 // Purple: Deeper analysis
    };
    static constexpr RGB RUNNING = {
        .red = 0, .green = 255, .blue = 0 // Green: Execution
    };

    // Error States
    static constexpr RGB GENERAL_ERROR = {
        .red = 255, .green = 0, .blue = 0 // Red: Total failure
    };
    static constexpr RGB TOKEN_ERROR = {
        .red = 255, .green = 0, .blue = 127 // Pinkish-Red: Syntax/Parsing issue
    };
    static constexpr RGB INTERPRET_ERROR = {
        .red = 255, .green = 102, .blue = 0 // Deep Orange: Logic/Runtime issue
    };
    static constexpr RGB WARN = {
        .red = 255,
        .green = 255,
        .blue = 0 // Pure Yellow: "Attention required, but still running"
    };
    static constexpr RGB RESTART = {
        .red = 0,
        .green = 0,
        .blue = 255
    };

    static void showColor(RGB color) {
        led_strip_set_pixel(StatusLEDExpression::statusLight, 0, color.red, color.green, color.blue);
        led_strip_refresh(StatusLEDExpression::statusLight);
        // StatusLEDExpression::leds[0] = Rgb{color.red, color.green, color.blue};
        // StatusLEDExpression::leds.show();
    }


    inline std::string colorize(const std::string &text, Color color) {
        return "\033[" + std::to_string(static_cast<int>(color)) + "m" + text + "\033[0m";
    }

    inline void runTimeError(const std::string &value) {
        std::cout << colorize("[ERROR] " + value, Color::RED) << std::endl;
        showColor(INTERPRET_ERROR);
    }

    inline void log(const std::string &value) {
        std::cout << colorize("[LOG] " + value, Color::CYAN) << std::endl;
    }

    inline void warn(const std::string &value) {
        std::cout << colorize("[WARN] " + value, Color::YELLOW) << std::endl;
        showColor(WARN);
    }

    inline int colorIndex = 0;

    template<typename T>
    T pq(const T &value, const std::string &prefix = "PRINTED") {
        std::string p = prefix;
        if (!p.empty()) p[0] = static_cast<char>(std::toupper(p[0]));

        Color color;
        switch (colorIndex) {
            case 0: color = Color::RED;
                break;
            case 1: color = Color::BLUE;
                break;
            case 2: color = Color::GREEN;
                break;
            case 3: color = Color::PURPLE;
                break;
            case 4: color = Color::CYAN;
                break;
            case 5: color = Color::YELLOW;
                break;
            default: color = Color::CYAN;
                break;
        }

        std::cout << debug::colorize("[" + p + "] " + value, color) << std::endl;
        std::cout.flush();

        colorIndex = (colorIndex + 1) % 6;
        return value;
    }

    template<typename T>
    T pqr(const T &value) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dist(0, 100);
        return pq(value, std::to_string(dist(gen)));
    }

    inline void print(const std::string &value) {
        pq<std::string>(value);
    }

    inline std::chrono::milliseconds getCurrentMs() {
        auto now = std::chrono::system_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    }
} // namespace debug
#include <string>

namespace utils {
    template<size_t N>
    std::string bytesToString(const uint8_t (&data)[N]) {
        return {reinterpret_cast<const char *>(data), N};
    }

    inline bool is_number(const std::string &s) {
        return !s.empty() && std::ranges::find_if(s, [](unsigned char c) { return !std::isdigit(c); }) == s.end();
    }
}


#endif //PHISILANDINTERPRETER_UTILS_H
