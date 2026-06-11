//
// Created by Ezra Golombek on 11/06/2026.
//

#include "logging/Logger.h"

#include "Utils.h"
#include "logging/Color.h"

void Logger::log(const std::string &contents) {
    std::cout << (apply(Color::BOLD) + apply(Color::BRIGHT_CYAN) + "[LOG] " + apply(Color::RESET) +
                  apply(Color::BRIGHT_WHITE) + contents);
}

void Logger::warn(const std::string &contents) {
    std::cout << (apply(Color::BOLD) + apply(Color::YELLOW) + "[WARN] " + apply(Color::RESET) +
                  apply(Color::BRIGHT_WHITE) + contents) << std::endl;
    debug::showColor(debug::WARN);
}

void Logger::bootMessage(const std::string &contents) {
    std::cout << (apply(Color::BOLD) + apply(Color::BRIGHT_BLUE) + "[BOOT] " + apply(Color::RESET) +
                  apply(Color::BRIGHT_WHITE) + contents) << std::endl;
}

void Logger::configuration(const std::string &contents) {
    std::cout << (apply(Color::BOLD) + apply(Color::BRIGHT_BLUE) + "[CONFIG] " + apply(Color::RESET) +
                  apply(Color::BRIGHT_WHITE) + contents) << std::endl;
}

void Logger::error(const std::string &contents) {
    std::cout << (apply(Color::BOLD) + apply(Color::RED) + "[ERROR] " + apply(Color::RESET) + apply(Color::BRIGHT_WHITE)
                  + contents) << std::endl;
    debug::showColor(debug::INTERPRET_ERROR);
}
