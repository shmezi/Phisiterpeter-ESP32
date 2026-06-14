//
// Created by Ezra Golombek on 11/06/2026.
//

#ifndef PHISITERPETER_ESP32_VERSION_H
#define PHISITERPETER_ESP32_VERSION_H
#include <string>
inline constexpr int MAJOR = 1, MINOR = 0, PATCH = 0;

inline const std::string &getVersion() {
    static const std::string v =
            std::to_string(MAJOR) + "." +
            std::to_string(MINOR) + "." +
            std::to_string(PATCH);
    return v;
}
#endif //PHISITERPETER_ESP32_VERSION_H
