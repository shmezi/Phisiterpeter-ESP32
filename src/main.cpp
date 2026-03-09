#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"       // Main Wi-Fi driver functions
#include "esp_log.h"        // Logging (optional but recommended)
#include "esp_event.h"      // Event loop for connection status
#include "nvs_flash.h"      // NVS flash for storing Wi-Fi credentials
#include "esp_netif.h"      // Network interface layer
#include "esp_err.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "driver/spi_common.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"
#include "Utils.h"
#include "../../../.platformio/packages/toolchain-riscv32-esp/riscv32-esp-elf/include/c++/14.2.0/thread"
#include "base/Interpreter.h"
#include "base/ScheduleLoop.h"
#include "base/Scope.h"
#include "base/Tokenizer.h"
#include "esp_task_wdt.h" // Make sure you include this header
#include "freertos/FreeRTOS.h"
#include "driver/uart.h"


#define PIN_NUM_POWER 10
#define PIN_NUM_MISO 7
#define PIN_NUM_MOSI 6
#define PIN_NUM_CLK  5
#define PIN_NUM_CS   4

#define TAG "UART_RECEIVER"
#define RX_BUF_SIZE 1024
#define TX_BUF_SIZE 1024 // We don't need a TX buffer for only receiving
#define UART_PORT_NUM UART_NUM_2 // Using UART2
#define RX_PIN 39 // Example pin, connect to the other device's TX
#define TX_PIN 40 // Example pin, connect to the other device's RX
#include <dirent.h> // Required for directory operations
#include <esp_adc/adc_oneshot.h>

#include "expressions/game/functions/AnalogReadExpression.h"


uint8_t data_buffer[128]; // Buffer to store received data
constexpr size_t buffer_size = sizeof(data_buffer); // Get the actual size ONCE


void uart_init() {
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    // Configure UART parameters
    ESP_ERROR_CHECK(uart_param_config(UART_PORT_NUM, &uart_config));

    // Set UART pins (TX, RX, RTS, CTS)
    ESP_ERROR_CHECK(uart_set_pin(UART_PORT_NUM, TX_PIN, RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    // Install UART driver, allocating the buffer
    ESP_ERROR_CHECK(uart_driver_install(UART_PORT_NUM, RX_BUF_SIZE, TX_BUF_SIZE, 0, NULL, 0));
}

void uart(void *pvParameters) {
    auto *data = static_cast<uint8_t *>(malloc(RX_BUF_SIZE + 1));
    for (;;) {
        const int rxBytes = uart_read_bytes(UART_PORT_NUM, data, RX_BUF_SIZE, pdMS_TO_TICKS(10));
        if (rxBytes > 0) {
            data[rxBytes] = 0;

            auto actualData = reinterpret_cast<char *>(data);
            // cout << actualData << endl;
            if (actualData[0] != '~')
                continue;
            auto prettyData = string(actualData);
            prettyData.erase(0, 1);

            ScheduleLoop::getInstance()->startEvent(std::stoi(prettyData));
        }
        vTaskDelay(pdMS_TO_TICKS(1)); // Delay for 1000ms
    }
}

void runClock(void *pvParameters) {
    for (;;) {
        ScheduleLoop::getInstance()->loop();

        vTaskDelay(pdMS_TO_TICKS(10)); // Delay for 1000ms

        // debug::print("loop test");
    }
}


void startup() {
    const auto c = "PhisilandInterpreter - (c) Created and developed by Ezra Golombek all rights reserved.";
    cout << debug::colorize(c, debug::Color::CYAN);

    cout << debug::colorize("© Developed and designed by Ezra Golombek 2025", debug::Color::BLUE) << endl;


    cout << "\033[0m\t\t" << endl;
}

void printStartupMessage() {
    const auto c = R"(  _   _               _                  _____  _                                             _
 | \ | |             | |                |  __ \| |                                           | |
 |  \| | _____      _| |_ ___  _ __  ___| |__) | | __ _ _   _  __ _ _ __ ___  _   _ _ __   __| |
 | . ` |/ _ \ \ /\ / / __/ _ \| '_ \/ __|  ___/| |/ _` | | | |/ _` | '__/ _ \| | | | '_ \ / _` |
 | |\  |  __/\ V  V /| || (_) | | | \__ \ |    | | (_| | |_| | (_| | | | (_) | |_| | | | | (_| |
 |_| \_|\___| \_/\_/  \__\___/|_| |_|___/_|    |_|\__,_|\__, |\__, |_|  \___/ \__,_|_| |_|\__,_|
                                                         __/ | __/ |
                                                        |___/ |___/
)";
    cout << debug::colorize(c, debug::Color::CYAN);

    cout << debug::colorize("© Developed and designed by Ezra Golombek 2025", debug::Color::BLUE) << endl;


    cout << "\033[0m\t\t" << endl;
}


void setupGPIO() {
    ESP_ERROR_CHECK(
        led_strip_new_rmt_device(
            &StatusLEDExpression::strip_config,
            &StatusLEDExpression::rmt_config,
            &StatusLEDExpression::statusLight));


    uart_init();


    //Analog pin registration
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&AnalogReadExpression::init_config_a, &AnalogReadExpression::adc_handle_a));
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&AnalogReadExpression::init_config_b, &AnalogReadExpression::adc_handle_b));
}

void connectWifi() {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    // 1. Scan for networks
    wifi_scan_config_t scan_config = {.ssid = 0, .bssid = 0, .channel = 0, .show_hidden = false};
    esp_wifi_scan_start(&scan_config, true); // true = blocking mode

    // 2. Retrieve results
    uint16_t ap_count = 0;
    esp_wifi_scan_get_ap_num(&ap_count);
    wifi_ap_record_t *ap_list = (wifi_ap_record_t *) malloc(sizeof(wifi_ap_record_t) * ap_count);
    esp_wifi_scan_get_ap_records(&ap_count, ap_list);
    vTaskDelay(pdMS_TO_TICKS(10000)); //Delay start to allow for monitor

    // 3. Print network info (Example)
    for (int i = 0; i < ap_count; i++) {
        printf("SSID: %s, RSSI: %d\n", ap_list[i].ssid, ap_list[i].rssi);
    }
    free(ap_list);

    // 4. Connect to a specific network
    // wifi_config_t wifi_config = {
    //     .sta = {
    //         .ssid = "YOUR_SSID",
    //         .password = "YOUR_PASSWORD",
    //     },
    // };
    // esp_wifi_set_mode(WIFI_MODE_STA);
    // esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    // esp_wifi_connect();
}


void runInterpreter() {
    {
        gpio_install_isr_service(0);
        std::shared_ptr<Scope> scope = std::make_shared<Scope>("headScope", nullptr);
        debug::log("Starting tokenization process");
        debug::showColor(debug::TOKENIZATION);


        // Tokenizer tokenizer = Tokenizer(*f, scope);
        // tokenizer.tokenize();
        // debug::log("Starting interpretation process");
        // debug::showColor(debug::INTERPRETATION);
        // Interpreter interpreter = Interpreter(scope, tokenizer.tokens);
        printStartupMessage();
        // debug::showColor(debug::RUNNING);
        // interpreter.run();

        xTaskCreate(
            runClock, // Function that implements the task.
            "MyForeverTask", // Text name for the task.
            32768, // Stack size in bytes, adjust as needed.
            nullptr, // Parameter passed into the task.
            0, // Priority, with 0 being the lowest.
            nullptr // Used to pass back the created task's handle.
        );
        xTaskCreate(
            uart, // Function that implements the task.
            "UART", // Text name for the task.
            32768, // Stack size in bytes, adjust as needed.
            nullptr, // Parameter passed into the task.
            10, // Priority, with 0 being the lowest.
            nullptr // Used to pass back the created task's handle.
        );
    }
}


extern "C" void app_main(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    vTaskDelay(pdMS_TO_TICKS(3000)); //Delay start to allow for monitor

    setupGPIO();
    connectWifi();

    runInterpreter();


    debug::log("Interpretation has finished! Background tasks are still running fear not!");
}
