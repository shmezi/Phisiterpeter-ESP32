//
// Created by Ezra Golombek on 02/12/2025.
//

#ifndef PHISITERPETER_ESP32_SCHEDULELOOP_H
#define PHISITERPETER_ESP32_SCHEDULELOOP_H
#include <atomic>
#include <chrono>
#include <functional>
#include <map>
#include <set>
#include "freertos/FreeRTOS.h"
#include <freertos/task.h>


class ScheduleLoop {
    std::atomic<bool> active = false;

    std::map<std::string, std::vector<std::function<void(int)> > > startFunc{};

    std::vector<std::function<void()> > always{};

    std::vector<std::pair<std::function<bool()>, std::function<void()> > > conditionalTasks{};

    std::vector<std::pair<std::function<bool()>, std::function<void()> > > whileTasks{};


    std::map<int, std::vector<std::function<void()> > > scheduled{};

    std::map<int, std::vector<std::function<void()> > > delayedTask{};

    std::map<int, std::chrono::milliseconds> lastScheduleRun{};

    std::map<int, std::function<void()> > idToTask{};

    std::set<int> taskIds{};

    void evaluateAndRunCooldown(const int &cooldown, std::chrono::milliseconds &lastRun);

public:
    static TaskHandle_t interpreterTaskHandle;

    static ScheduleLoop *getInstance();

    void loop();

    void startEvent(int param);

    ScheduleLoop();

    void stop();

    void start();

    void onEventListener(const std::string &id, std::function<void(int)> task);

    void addTask(const std::function<void()> &task);

    void addConditionalTask(const std::function<bool()> &condition, std::function<void()> task);

    void addCooldownTask(int cooldown, const std::function<void()> &task);

    void runAfterPeriod(const int &cooldown, std::function<void()> task);

    int newIDTask(std::function<void()> task);

    void queueIDTask(int id);
};


#endif //PHISITERPETER_ESP32_SCHEDULELOOP_H
