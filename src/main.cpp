#include <cstdio>
#include <cstring>
#include <esp_mac.h>
#include <iostream>
#include <memory>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"       // Main Wi-Fi driver functions
#include "esp_log.h"        // Logging (optional but recommended)
#include "esp_event.h"      // Event loop for connection status
#include "nvs_flash.h"      // NVS flash for storing Wi-Fi credentials
#include "esp_netif.h"      // Network interface layer
#include "esp_err.h"
#include "esp_vfs_fat.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"
#include "Utils.h"
#include "../../../.platformio/packages/toolchain-riscv32-esp/riscv32-esp-elf/include/c++/14.2.0/thread"
#include "base/ScheduleLoop.h"
#include "base/Scope.h"
#include "esp_task_wdt.h" // Make sure you include this header
#include "base/DovetailCore.h"
#include "base/Interpreter.h"
#include "base/Tokenizer.h"
using namespace std;
#include "esp_http_server.h"

#define PIN_NUM_POWER 10
#define PIN_NUM_MISO 7
#define PIN_NUM_MOSI 6
#define PIN_NUM_CLK  5
#define PIN_NUM_CS   4


#define RX_BUF_SIZE 1024
#define TX_BUF_SIZE 1024 // We don't need a TX buffer for only receiving
#define RX_PIN 39 // Example pin, connect to the other device's TX
#define TX_PIN 40 // Example pin, connect to the other device's RX
#include <dirent.h> // Required for directory operations
#include <esp_adc/adc_oneshot.h>

#include "expressions/game/functions/AnalogReadExpression.h"


uint8_t data_buffer[128]; // Buffer to store received data
constexpr size_t buffer_size = sizeof(data_buffer); // Get the actual size ONCE


void startup() {
    const auto c = "PhisilandInterpreter - (c) Created and developed by Ezra Golombek all rights reserved.";
    cout << debug::colorize(c, debug::Color::CYAN);

    cout << debug::colorize("© Developed and designed by Ezra Golombek 2025", debug::Color::BLUE) << endl;


    cout << "\033[0m\t\t" << endl;
}



void setupGPIO() {
    AnalogReadExpression::init_config_a.unit_id = ADC_UNIT_1;
    AnalogReadExpression::init_config_a.clk_src = ADC_RTC_CLK_SRC_DEFAULT;
    AnalogReadExpression::init_config_b.unit_id = ADC_UNIT_2;
    AnalogReadExpression::init_config_b.clk_src = ADC_RTC_CLK_SRC_DEFAULT;
    ESP_ERROR_CHECK(
        led_strip_new_rmt_device(
            &StatusLEDExpression::strip_config,
            &StatusLEDExpression::rmt_config,
            &StatusLEDExpression::statusLight));


    //Analog pin registration
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&AnalogReadExpression::init_config_a, &AnalogReadExpression::adc_handle_a));
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&AnalogReadExpression::init_config_b, &AnalogReadExpression::adc_handle_b));
}


extern "C" void app_main(void) {
    vTaskDelay(pdMS_TO_TICKS(3000)); //Delay start to allow for monitor
    esp_log_level_set("wifi", ESP_LOG_VERBOSE);
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    debug::showColor(debug::STARTUP);


    setupGPIO();
    DovetailCore::innitDovetail();
    uint8_t mac[6];
    esp_read_mac(mac, ESP_MAC_WIFI_STA);
    DovetailCore::sendGetRequest("register?mac=" + DovetailCore::getMacAddress());
    if (DovetailCore::sendGetRequest("code?mac=" + DovetailCore::getMacAddress()))
        debug::showColor(debug::CODE_LOADED);


    debug::log("Interpretation has finished! Background tasks are still running fear not!");
}
