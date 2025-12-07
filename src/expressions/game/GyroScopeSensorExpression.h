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

    mpu6050_handle_t dev_hdl;
    std::deque<float> results = std::deque<float>();

public:
    static i2c_master_bus_config_t i2c0_bus_cfg;
    static i2c_master_bus_handle_t i2c0_bus_hdl;
    std::string expressionName() override;




    float pushResult(float newResult);

    std::unique_ptr<Expression> interpret(std::shared_ptr<Scope> scope) override;

    std::string interpertAsString(std::shared_ptr<Scope> scope) override;

    GyroScopeSensorExpression(bool toggle);
};
#endif //PHISITERPETER_ESP32_GYROSCOPESENSOR_H
