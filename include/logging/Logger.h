//
// Created by Ezra Golombek on 11/06/2026.
//

#ifndef PHISITERPETER_ESP32_LOGGER_H
#define PHISITERPETER_ESP32_LOGGER_H
#include <iostream>
#include <string>

class Logger {
public:
    static void log(const std::string &contents);

    static void warn(const std::string &contents);

    static void bootMessage(const std::string &contents);

    static void configuration(const std::string &contents);

    static void error(const std::string &contents);
};


#endif //PHISITERPETER_ESP32_LOGGER_H
