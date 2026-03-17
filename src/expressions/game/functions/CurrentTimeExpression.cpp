//
// Created by Ezra Golombek on 07/12/2025.
//

#include "../../../../include/expressions/game/functions/CurrentTimeExpression.h"
#include <sys/time.h> // Required for gettimeofday
#include <esp_log.h>  // For ESP_LOGI
#include <esp_timer.h>

#include "expressions/value/NumberExpression.h"

std::string CurrentTimeExpression::expressionName() {
    return "now";
}

std::shared_ptr<Expression> CurrentTimeExpression::interpret(std::shared_ptr<Scope> scope) {

    return std::make_shared<NumberExpression>(esp_timer_get_time());
}

std::string CurrentTimeExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}
