//
// Created by Ezra Golombek on 05/12/2025.
//

#ifndef PHISITERPETER_ESP32_GYROSCOPESENSOR_H
#define PHISITERPETER_ESP32_GYROSCOPESENSOR_H
#include <deque>

#include "mpu6050.h"
#include "Utils.h"
#include "expressions/Expression.h"
#include "freertos/FreeRTOS.h"

#define TSK_MINIMAL_STACK_SIZE         (1024)

#define I2C0_MASTER_PORT               I2C_NUM_0
#define I2C0_MASTER_SDA_IO             GPIO_NUM_1 // blue
#define I2C0_MASTER_SCL_IO             GPIO_NUM_2 // yellow


class GyroScopeSensorExpression : public Expression {
    mpu6050_config_t dev_cfg;
    i2c_master_bus_config_t i2c0_bus_cfg;
    i2c_master_bus_handle_t i2c0_bus_hdl;
    mpu6050_handle_t dev_hdl;
    std::deque<float> results = std::deque<float>();
public:
    std::string expressionName() override;


    float pushResult(float newResult);

    std::unique_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    GyroScopeSensorExpression() {
        dev_cfg = I2C_MPU6050_CONFIG_DEFAULT;
        i2c0_bus_cfg = {
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
        ESP_ERROR_CHECK(i2c_new_master_bus(&i2c0_bus_cfg, &i2c0_bus_hdl));

        /* check i2c master bus handle instance */
        if (i2c0_bus_hdl == nullptr) {
            debug::error("i2c master bus handle init failed");
            assert(&i2c0_bus_hdl);
        }

        mpu6050_init(i2c0_bus_hdl, &dev_cfg, &dev_hdl);
        if (dev_hdl == nullptr) {
            debug::error("mpu6050 handle init failed");
            assert(dev_hdl);
        }
    };
};


#endif //PHISITERPETER_ESP32_GYROSCOPESENSOR_H
