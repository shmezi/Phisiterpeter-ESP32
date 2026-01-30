//
// Created by Ezra Golombek on 22/01/2026.
//

#include "expressions/game/objects/EncoderSensorExpression.h"

#include <chrono>

#include "as5600.hpp"
#include "i2c.hpp"
#include "task.hpp"
#include "Utils.h"
#include "expressions/internal/VoidExpression.h"

#include "expressions/value/NumberExpression.h"


std::string EncoderSensorExpression::expressionName() {
    return "encoder";
}

#include "driver/i2c_master.h" // Native New Driver
#include <functional>

std::shared_ptr<Expression> EncoderSensorExpression::interpret(std::shared_ptr<Scope> scope) {
//     // 1. Initialize the New Master Bus (Native IDF)
//     static i2c_master_bus_handle_t bus_handle = [] {
//         i2c_master_bus_config_t bus_config = {
//             .i2c_port = I2C_NUM_1,
//             .sda_io_num = (gpio_num_t) 8,
//             .scl_io_num = (gpio_num_t) 9,
//             .clk_source = I2C_CLK_SRC_DEFAULT,
//             .glitch_ignore_cnt = 7,
//             .flags = {.enable_internal_pullup = true}
//         };
//         i2c_master_bus_handle_t handle;
//         ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &handle));
//         return handle;
//     }();
//
//     // 2. Initialize the Device Handle (Native IDF)
//     static i2c_master_dev_handle_t dev_handle = [](i2c_master_bus_handle_t bus) {
//         i2c_device_config_t dev_cfg = {
//             .dev_addr_length = I2C_ADDR_BIT_LEN_7,
//             .device_address = 0x36,
//             .scl_speed_hz = 400000,
//         };
//         i2c_master_dev_handle_t handle;
//         ESP_ERROR_CHECK(i2c_master_bus_add_device(bus, &dev_cfg, &handle));
//         return handle;
//     }(bus_handle);
//
//     // 3. Initialize AS5600 using the Native handles via lambda
//     static constexpr float encoder_update_period = 0.01f;
//     static espp::As5600 as5600({
//         .write_then_read = [](uint8_t dev_addr, const uint8_t *write_data, size_t write_len,
//                               uint8_t *read_data, size_t read_len) -> bool {
//             // This calls the actual NEW driver directly
//             return i2c_master_transmit_receive(dev_handle, write_data, write_len,
//                                                read_data, read_len, 100) == ESP_OK;
//         },
//         .update_period = std::chrono::duration<float>(encoder_update_period),
//         .log_level = espp::Logger::Verbosity::WARN
//     });
//     // printf("Encoder Raw -> Degrees: %.2f, Count: %d\n", as5600.get_degrees(), as5600.get_count());
//
//     uint8_t status;
//     uint8_t agc;
//     // Register 0x0B is Status, 0x1A is AGCfx
//     i2c_master_transmit_receive(dev_handle, (uint8_t[]){0x0B}, 1, &status, 1, 100);
//     i2c_master_transmit_receive(dev_handle, (uint8_t[]){0x1A}, 1, &agc, 1, 100);
//
//     bool magnet_low = status & (1 << 4);  // ML bit
//     bool magnet_high = status & (1 << 3); // MH bit
//     bool magnet_ok = status & (1 << 5);   // MD bit
//
//     printf("Status: %02X (OK: %d, Low: %d, High: %d) | AGC: %d\n",
//             status, magnet_ok, magnet_low, magnet_high, agc);

    // return std::make_shared<NumberExpression>(as5600.get_degrees());
return std::make_shared<VoidExpression>();
}


std::string EncoderSensorExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return interpret(scope)->interpertAsString(scope);
}
