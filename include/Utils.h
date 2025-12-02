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

#include "../../../.platformio/packages/toolchain-riscv32-esp/riscv32-esp-elf/include/c++/14.2.0/chrono"

namespace debug {
    enum class Color {
        RED = 31,
        BLUE = 34,
        GREEN = 32,
        PURPLE = 35,
        CYAN = 36,
        YELLOW = 33,
    };

    inline std::string colorize(const std::string &text, Color color) {
        return "\033[" + std::to_string(static_cast<int>(color)) + "m" + text + "\033[0m";
    }

    inline void error(const std::string &value) {
        std::cout << colorize("[ERROR] " + value, Color::RED) << std::endl;
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

inline bool is_number(const std::string &s) {
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

#endif //PHISILANDINTERPRETER_UTILS_H
