//
// Created by Ezra Golombek on 02/12/2025.
//

#ifndef PHISITERPETER_ESP32_SCHEDULELOOP_H
#define PHISITERPETER_ESP32_SCHEDULELOOP_H
#include <atomic>
#include <chrono>
#include <functional>
#include <map>


class ScheduleLoop {
    std::atomic<bool> active = false;
    // static ScheduleLoop *instance;

    std::vector<std::function<void()> > always = std::vector<std::function<void()> >();
    std::vector<std::pair<std::function<bool()>, std::function<void()> > > conditionalTasks =
            std::vector<std::pair<std::function<bool()>, std::function<void()> > >();


    std::map<int, std::vector<std::function<void()> > > scheduled = std::map<int, std::vector<std::function<void
        ()> > >();
    std::map<int, std::chrono::milliseconds> lastScheduleRun = std::map<int, std::chrono::milliseconds>();




    void evaluateAndRunCooldown(const int &cooldown, std::chrono::milliseconds &lastRun);

public:
    static ScheduleLoop *getInstance();
    void loop();
    ScheduleLoop();

    void stop();

    void start();

    void addTask(std::function<void()> task);

    void addConditionalTask(std::function<bool()> condition, std::function<void()> task);

    void addCooldownTask(int cooldown, std::function<void()> task);
};


#endif //PHISITERPETER_ESP32_SCHEDULELOOP_H
