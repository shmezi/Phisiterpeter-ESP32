//
// Created by Ezra Golombek on 09/06/2026.
//

#include "base/dovetail/DovetailClient.h"

#include <esp_err.h>
#include <esp_http_client.h>


#include "Utils.h"
#include "base/Interpreter.h"
#include "base/dovetail/DovetailCore.h"

std::string DovetailClient::incomingData;

esp_err_t DovetailClient::httpClientHandler(esp_http_client_event_t *evt) {
    switch (evt->event_id) {
        case HTTP_EVENT_ON_CONNECTED:
            // Clear the string for a fresh start
            incomingData.clear();
            break;


        case HTTP_EVENT_ON_DATA:
            if (evt->data_len > 0) {
                // Safely append the incoming chunk to our string
                incomingData.append(static_cast<char *>(evt->data), evt->data_len);
            }
            break;

        case HTTP_EVENT_ON_FINISH: {
            char url_buffer[128];
            // Get the URL that was just requested
            esp_http_client_get_url(evt->client, url_buffer, sizeof(url_buffer));
            if (strstr(url_buffer, "/code")) {
                // WE can push this back if we see this doesnt function..
                debug::log("Code command!");
                DovetailCore::codebase = incomingData;
                // Trigger your interpreter here or set a flag
                Interpreter::runInterpreter(DovetailCore::codebase);
            }
            break;
        }
        default:
            break;
    }
    return ESP_OK;
}


bool DovetailClient::sendGetRequest(const std::string &url) {
    std::string full_url = "http://192.168.4.1/" + url;

    esp_http_client_config_t config = {
        .url = full_url.c_str(),
        .method = HTTP_METHOD_GET,
        .event_handler = httpClientHandler,
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = esp_http_client_perform(client);
    esp_http_client_cleanup(client);
    if (err != ESP_OK) {
        debug::runTimeError("HTTP GET request to " + url + " failed :( Error: " + std::string(esp_err_to_name(err)));
        return false;
    }
    return true;
}
