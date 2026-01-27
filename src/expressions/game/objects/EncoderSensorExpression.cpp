//
// Created by Ezra Golombek on 22/01/2026.
//

#include "expressions/game/objects/EncoderSensorExpression.h"

#include <chrono>
#include <sdkconfig.h>
#include <vector>
#include <soc/gpio_num.h>

#include "expressions/internal/VoidExpression.h"
#include "as5600.hpp"
#include "i2c.hpp"
#include "task.hpp"
#include "expressions/value/NumberExpression.h"


std::string EncoderSensorExpression::expressionName() {
    return "encoder";
}

std::shared_ptr<Expression> EncoderSensorExpression::interpret(std::shared_ptr<Scope> scope) {
    static espp::I2c i2c({
        .port = I2C_NUM_1,
        .sda_io_num = static_cast<gpio_num_t>(17),
        .scl_io_num = static_cast<gpio_num_t>(18),
    });

    static constexpr float encoder_update_period = 0.01f; // seconds
    static espp::As5600 encoder(
        {
            .write_then_read =
            std::bind(&espp::I2c::write_read, &i2c, std::placeholders::_1, std::placeholders::_2,
                      std::placeholders::_3, std::placeholders::_4, std::placeholders::_5),

            .update_period = std::chrono::duration<float>(encoder_update_period),
            .log_level = espp::Logger::Verbosity::WARN
        });

    auto count = encoder.get_count();
    auto radians = encoder.get_radians();
    auto degrees = encoder.get_degrees();
    auto rpm = encoder.get_rpm();

    return std::make_shared<NumberExpression>(degrees);
}



std::string EncoderSensorExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "";
}
