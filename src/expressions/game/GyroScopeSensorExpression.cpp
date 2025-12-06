//
// Created by Ezra Golombek on 05/12/2025.
//

#include "GyroScopeSensorExpression.h"

#include <algorithm>
#include <esp_log.h>
#include <mpu6050.h>
#include <portmacro.h>
#include <freertos/task.h>

#include "Utils.h"
#include "expressions/internal/VoidExpression.h"
#include "expressions/value/NumberExpression.h"

std::string GyroScopeSensorExpression::expressionName() {
    return "gyro";
}

std::unique_ptr<Expression> GyroScopeSensorExpression::interpret(std::shared_ptr<Scope> scope) {
    float temperature;
    mpu6050_gyro_data_axes_t gyro_data;
    mpu6050_accel_data_axes_t accel_data;
    esp_err_t result = mpu6050_get_motion(dev_hdl, &gyro_data, &accel_data, &temperature);
    if (result != ESP_OK) {
        ESP_LOGE("APP_TAG", "mpu6050 device read failed (%s)", esp_err_to_name(result));
        return std::make_unique<VoidExpression>();
    }
    /* pitch and roll */
    float pitch = atanf(accel_data.x_axis / sqrtf(powf(accel_data.y_axis, 2.0f) + powf(accel_data.z_axis, 2.0f)));
    float roll = atanf(accel_data.y_axis / sqrtf(powf(accel_data.x_axis, 2.0f) + powf(accel_data.z_axis, 2.0f)));

    ESP_LOGI("APP_TAG", "Accelerometer X-Axis: %fg", accel_data.x_axis);
    ESP_LOGI("APP_TAG", "Accelerometer Y-Axis: %fg", accel_data.y_axis);
    ESP_LOGI("APP_TAG", "Accelerometer Z-Axis: %fg", accel_data.z_axis);
    ESP_LOGI("APP_TAG", "Gyroscope X-Axis:     %f°/sec", gyro_data.x_axis);
    ESP_LOGI("APP_TAG", "Gyroscope Y-Axis:     %f°/sec", gyro_data.y_axis);
    ESP_LOGI("APP_TAG", "Gyroscope Z-Axis:     %f°/sec", gyro_data.z_axis);
    ESP_LOGI("APP_TAG", "Temperature:          %f°C", temperature);
    ESP_LOGI("APP_TAG", "Pitch Angle:          %f°", pitch);
    ESP_LOGI("APP_TAG", "Roll Angle:           %f°", roll);


    return std::make_unique<NumberExpression>(static_cast<int>(roll));
}

std::string GyroScopeSensorExpression::interpertAsString(std::shared_ptr<Scope> scope) {
    return "";
}
