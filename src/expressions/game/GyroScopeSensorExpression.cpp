//
// Created by Ezra Golombek on 05/12/2025.
//

#include "../../../include/expressions/game/GyroScopeSensorExpression.h"

#include <algorithm>
#include <esp_log.h>
#include <mpu6050.h>
#include <portmacro.h>
#include <freertos/task.h>

#include "Utils.h"
#include "../../../../../.platformio/packages/toolchain-riscv32-esp/riscv32-esp-elf/include/c++/14.2.0/complex"
#include "expressions/internal/VoidExpression.h"
#include "expressions/value/BooleanExpression.h"
#include "expressions/value/NumberExpression.h"
#include "expressions/value/TextExpression.h"
i2c_master_bus_handle_t GyroScopeSensorExpression::i2c0_bus_hdl = nullptr;
i2c_master_bus_config_t GyroScopeSensorExpression::i2c0_bus_cfg = {};

std::string GyroScopeSensorExpression::expressionName() {
    return "gyro";
}

static void initI2C() {
    /* check i2c master bus handle instance */
    if (GyroScopeSensorExpression::i2c0_bus_hdl != nullptr) {
        return;
    }
    GyroScopeSensorExpression::i2c0_bus_cfg = {
        .i2c_port = I2C0_MASTER_PORT,
        .sda_io_num = I2C0_MASTER_SDA_IO,
        .scl_io_num = I2C0_MASTER_SCL_IO,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,

        .flags = {

            .enable_internal_pullup = true
        }
    };
    //HERE
    /* instantiate i2c master bus 0 */
    ESP_ERROR_CHECK(
        i2c_new_master_bus(&GyroScopeSensorExpression::i2c0_bus_cfg, &GyroScopeSensorExpression::i2c0_bus_hdl));
    if (GyroScopeSensorExpression::i2c0_bus_hdl == nullptr) {
        debug::error("i2c master bus handle init failed");
        assert(&GyroScopeSensorExpression::i2c0_bus_hdl);
    }
}

GyroScopeSensorExpression::GyroScopeSensorExpression(bool toggle) {
    const uint16_t address = toggle ? 0x68 : 0x69;
    dev_cfg = {
        .i2c_address = UINT8_C(address),
        .i2c_clock_speed = I2C_MPU6050_DEV_CLK_SPD,
        .low_pass_filter = MPU6050_DIGITAL_LP_FILTER_ACCEL_260KHZ_GYRO_256KHZ,
        .gyro_clock_source = MPU6050_GYRO_CS_PLL_X_AXIS_REF,
        .gyro_full_scale_range = MPU6050_GYRO_FS_RANGE_500DPS,
        .accel_full_scale_range = MPU6050_ACCEL_FS_RANGE_4G
    };

    initI2C();

    mpu6050_init(i2c0_bus_hdl, &dev_cfg, &dev_hdl);
    if (dev_hdl == nullptr) {
        debug::error("mpu6050 handle init failed");
    } else {
        debug::log("mpu6050 init was a success!");
    }
}

float GyroScopeSensorExpression::pushResult(float newResult) {
    if (results.size() > 9) {
        results.pop_front();
    }
    results.push_back(newResult);
    float total = 0;
    for (const float result: results) {
        total += result;
    }
    return total / static_cast<float>(results.size());
}

std::shared_ptr<Expression> GyroScopeSensorExpression::interpret(std::shared_ptr<Scope> scope) {
    return shared_from_this();
}

float GyroScopeSensorExpression::pitch() const {
    mpu6050_gyro_data_axes_t gyro_data;
    mpu6050_accel_data_axes_t accel_data;
    float temperature;

    esp_err_t result = mpu6050_get_motion(dev_hdl, &gyro_data, &accel_data, &temperature);
    if (result != ESP_OK) {
        return 0.0f;
    }
    if (sqrtf(powf(accel_data.y_axis, 2.0f)) == 0.0f) {
        debug::error("Cant divide by zero!");
        return 0.0f;
    }
    float pitchValue = atanf(accel_data.x_axis / sqrtf(powf(accel_data.y_axis, 2.0f) + powf(accel_data.z_axis, 2.0f)));

    return pitchValue * 57.2958f;
}

float GyroScopeSensorExpression::role() const {
    mpu6050_gyro_data_axes_t gyro_data;
    mpu6050_accel_data_axes_t accel_data;
    float temperature;

    esp_err_t result = mpu6050_get_motion(dev_hdl, &gyro_data, &accel_data, &temperature);
    if (result != ESP_OK) {
        return 0.0f;
    }
    float rollValue = atanf(accel_data.y_axis / sqrtf(powf(accel_data.x_axis, 2.0f) + powf(accel_data.z_axis, 2.0f)));

    return rollValue * 57.2958f;
}

std::string GyroScopeSensorExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "gyroValue";
}
