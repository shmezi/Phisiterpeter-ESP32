//
// Created by Ezra Golombek on 07/12/2025.
//

#include "../../../include/expressions/game/CurrentTimeExpression.h"
#include <sys/time.h> // Required for gettimeofday
#include <esp_log.h>  // For ESP_LOGI

#include "expressions/value/NumberExpression.h"

std::string CurrentTimeExpression::expressionName() {
    return "now";
}

std::shared_ptr<Expression> CurrentTimeExpression::interpret(std::shared_ptr<Scope> scope) {
    timeval tv_now;
    gettimeofday(&tv_now, nullptr);


    int64_t time_ms = tv_now.tv_sec * 1000LL + static_cast<int64_t>(tv_now.tv_usec) / 1000LL;
    return std::make_shared<NumberExpression>(time_ms);
}

std::string CurrentTimeExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}
