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
#define PIN_NUM_MISO 4
#define PIN_NUM_MOSI 5
#define PIN_NUM_CLK  6
#define PIN_NUM_CS   7


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
            auto prettyData = string(actualData);
            prettyData.erase(0,1);
            // cout << stoi(prettyData) << endl;
            ScheduleLoop::getInstance()->startEvent(std::stoi(prettyData));
        }
    }
}

void runClock(void *pvParameters) {
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(10)); // Delay for 1000ms
        ScheduleLoop::getInstance()->loop();
        // debug::print("loop test");
    }
}


extern "C" void app_main(void) {
    gpio_set_direction(static_cast<gpio_num_t>(PIN_NUM_POWER), GPIO_MODE_OUTPUT);
    gpio_set_level(static_cast<gpio_num_t>(PIN_NUM_POWER), 1); // Power OFF
    vTaskDelay(pdMS_TO_TICKS(50)); // Wait for power discharge
    gpio_set_level(static_cast<gpio_num_t>(PIN_NUM_POWER), 0); // Power ON
    vTaskDelay(pdMS_TO_TICKS(200)); // Wait for SD card internal boot
    vTaskDelay(pdMS_TO_TICKS(2000)); // Wait for peripherals
    uart_init();

    esp_err_t ret;


    std::cout << "Initializing SPI bus...\n";

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
        std::cout << "Failed to initialize SPI bus: " << esp_err_to_name(ret) << "\n";
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

    std::cout << "Mounting filesystem...\n";
    ret = esp_vfs_fat_sdspi_mount("/sdcard", &host, &slot_config, &mount_config, &card);
    if (ret != ESP_OK) {
        std::cout << "Failed to mount SD card: " << esp_err_to_name(ret) << "\n";
        spi_bus_free(SPI2_HOST);
        return;
    }

    std::cout << "SD card mounted successfully!\n";

    // --- Write a file ---
    const char *file_path = "/sdcard/test.txt";
    FILE *f = fopen(file_path, "r");
    // if (f == nullptr) {
    //     std::cout << "Failed to open file for writing\n";
    // } else {
    //     fprintf(f, "Hello SD card!\n");
    //     fclose(f);
    //     std::cout << "File written successfully!\n";
    // }

    // --- Read back the file ---
    f = fopen(file_path, "r");
    if (f == nullptr) {
        std::cout << "Failed to open file for reading\n";
    } else {
        gpio_install_isr_service(0);
        std::shared_ptr<Scope> scope = std::make_shared<Scope>("headScope", nullptr);
        Tokenizer tokenizer = Tokenizer(*f, scope);
        tokenizer.tokenize();

        Interpreter interpreter = Interpreter(scope, tokenizer.tokens);
        interpreter.run();
        fclose(f);
        xTaskCreate(
            runClock, // Function that implements the task.
            "MyForeverTask", // Text name for the task.
            32768, // Stack size in bytes, adjust as needed.
            nullptr, // Parameter passed into the task.
            1, // Priority, with 0 being the lowest.
            nullptr // Used to pass back the created task's handle.
        );
        xTaskCreate(
            uart, // Function that implements the task.
            "UART", // Text name for the task.
            32768, // Stack size in bytes, adjust as needed.
            nullptr, // Parameter passed into the task.
            1, // Priority, with 0 being the lowest.
            nullptr // Used to pass back the created task's handle.
        );
        std::cout << "\nFile read complete.\n";
    }

    // --- Cleanup ---
    esp_vfs_fat_sdcard_unmount("/sdcard", card);
    spi_bus_free(SPI2_HOST);

    std::cout << "SD card unmounted, SPI bus freed.\n";
}
