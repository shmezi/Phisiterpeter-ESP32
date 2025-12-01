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
#include "base/Interpreter.h"
#include "base/Scope.h"
#include "base/Tokenizer.h"

#define PIN_NUM_MISO 4
#define PIN_NUM_MOSI 5
#define PIN_NUM_CLK  6
#define PIN_NUM_CS   7

extern "C" void app_main(void) {
    vTaskDelay(pdMS_TO_TICKS(2000)); // Wait for peripherals

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

    // --- FATFS mount configuration ---
    esp_vfs_fat_mount_config_t mount_config = {
        .format_if_mount_failed = false,
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
    //     // fprintf(f, "Hello SD card!\n");
    //     fclose(f);
    //     std::cout << "File written successfully!\n";
    // }

    // --- Read back the file ---
    f = fopen(file_path, "r");
    if (f == nullptr) {
        std::cout << "Failed to open file for reading\n";
    } else {
        std::shared_ptr<Scope> scope = std::make_shared<Scope>("headScope", nullptr);
        Tokenizer tokenizer = Tokenizer(*f, scope);
        tokenizer.tokenize();
        Interpreter interpreter = Interpreter(scope, tokenizer.tokens);
        interpreter.run();
        fclose(f);
        std::cout << "\nFile read complete.\n";
    }

    // --- Cleanup ---
    esp_vfs_fat_sdcard_unmount("/sdcard", card);
    spi_bus_free(SPI2_HOST);
    std::cout << "SD card unmounted, SPI bus freed.\n";
}
