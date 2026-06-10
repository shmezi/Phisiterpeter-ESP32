//
// Created by Ezra Golombek on 11/03/2026.
//

#ifndef PHISITERPETER_ESP32_DOVETAILCORE_H
#define PHISITERPETER_ESP32_DOVETAILCORE_H
#include <esp_event_base.h>
#include <esp_http_client.h>
#include <esp_http_server.h>
#include <esp_wifi_types_generic.h>
#include <string>

#include "../../../../../.platformio/packages/toolchain-riscv32-esp@14.2.0+20251107/riscv32-esp-elf/include/c++/14.2.0/vector"


#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

class DovetailCore {
public:
    static std::string codebase;


    static bool shouldUpdateCodeBase;

    static std::array<unsigned char, 6> selfMac;

    static std::string prettyMac;

    static SemaphoreHandle_t shutdownWS;

    static std::vector<wifi_ap_record_t> scanNetworks();

    static bool isDovetailNetwork(const std::string &ssid);

    static void connectToNetwork(const wifi_ap_record_t &network);

    static bool verifyRegistration();

    static bool verifyConnection();

    static void onFailedNetworkScan();

    static bool hasDovetailRegistered();

    static void scanAndConnect();

    static std::string getFormattedMacAddress();

    static std::array<unsigned char, 6> getMacAddress();

    static void loadCodebase();

    static void loadAndExecuteCodebase();

    static void retrieveCodebaseAndInterpert();

    static SemaphoreHandle_t dovetailRegisteredSuccessfully;


    static void innitDovetail();
};


#endif //PHISITERPETER_ESP32_DOVETAILCORE_H
