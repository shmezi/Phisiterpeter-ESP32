#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>

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
#define RX_PIN 17 // Example pin, connect to the other device's TX
#define TX_PIN 18 // Example pin, connect to the other device's RX


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
            if (actualData[0] != '~')
                continue;
            debug::print("incoming message!");
            auto prettyData = string(actualData);
            prettyData.erase(0, 1);
            // cout << stoi(prettyData) << endl;
            ScheduleLoop::getInstance()->startEvent(std::stoi(prettyData));
        }
    }
}

void runClock(void *pvParameters) {
    for (;;) {
        ScheduleLoop::getInstance()->loop();

        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1000ms

        // debug::print("loop test");
    }
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

extern "C" void app_main(void) {
    vTaskDelay(pdMS_TO_TICKS(3000)); //Delay start to allow for monitor

    uart_init();

    esp_err_t ret;


    debug::log("Initializing SPI bus...");

    // --- SPI bus configuration ---
    spi_bus_config_t bus_cfg = {
        .mosi_io_num = static_cast<gpio_num_t>(PIN_NUM_MOSI),
        .miso_io_num = static_cast<gpio_num_t>(PIN_NUM_MISO),
        .sclk_io_num = static_cast<gpio_num_t>(PIN_NUM_CLK),
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };

    ret = spi_bus_initialize(SPI2_HOST, &bus_cfg, SDSPI_DEFAULT_DMA);
    if (ret != ESP_OK) {
        debug::error("Failed to initialize SPI bus!");
        return;
    }

    // --- Host configuration ---
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    host.slot = SPI2_HOST;

    // --- Device configuration ---
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = static_cast<gpio_num_t>(PIN_NUM_CS);
    slot_config.host_id = SPI2_HOST;


    const char *aMessage = "2\n";
    uart_write_bytes(UART_NUM_2, aMessage, strlen(aMessage));


    // --- FATFS mount configuration ---
    esp_vfs_fat_mount_config_t mount_config = {
        .format_if_mount_failed = true,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024,
    };

    sdmmc_card_t *card;

    debug::log("Mounting filesystem...");
    ret = esp_vfs_fat_sdspi_mount("/sdcard", &host, &slot_config, &mount_config, &card);
    if (ret != ESP_OK) {
        debug::error("Failed to mount SD card!");
        spi_bus_free(SPI2_HOST);
        return;
    }

    debug::log("SD card mounted successfully!");


    const char *file_path = "/sdcard/code.txt";


    FILE *f = fopen(file_path, "r");
    if (f == nullptr) {
        debug::error("File could not be opened!");
    } else {
        gpio_install_isr_service(0);
        std::shared_ptr<Scope> scope = std::make_shared<Scope>("headScope", nullptr);
        debug::log("Starting tokenization process");
        Tokenizer tokenizer = Tokenizer(*f, scope);
        tokenizer.tokenize();
        debug::log("Starting interpretation process");
        Interpreter interpreter = Interpreter(scope, tokenizer.tokens);
        printStartupMessage();
        interpreter.run();
        fclose(f);
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

    // --- Cleanup ---
    esp_vfs_fat_sdcard_unmount("/sdcard", card);
    spi_bus_free(SPI2_HOST);

    debug::log("Interpertation has finished! Background tasks are still running fear not!");
}
