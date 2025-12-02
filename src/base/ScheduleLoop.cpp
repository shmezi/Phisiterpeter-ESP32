//
// Created by Ezra Golombek on 02/12/2025.
//

#include "base/ScheduleLoop.h"

#include <algorithm>
#include <thread>

#include "Utils.h"

// static auto MAINSCHEDULER = ScheduleLoop();

void ScheduleLoop::checkFunction(const int &cooldown, std::chrono::milliseconds &lastRun) {
    const auto currentTime = debug::getCurrentMs();

    if ((currentTime - lastRun).count() >= cooldown) {
        for (auto function: scheduled[cooldown]) {
            function();
        }
        lastScheduleRun[cooldown] = currentTime;
    }
}


void ScheduleLoop::loop() {
    while (active) {
        for (auto [condition, task]: conditionalTasks) {
            if (condition()) {
                task();
            }
        }
        for (auto task: always) {
            task();
        }
        for (auto &[cooldown, lastRun]: lastScheduleRun) {
            checkFunction(cooldown, lastRun);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

ScheduleLoop::ScheduleLoop() {
    start();
}

void ScheduleLoop::stop() {
    active = false;
}

void ScheduleLoop::start() {
    active = true;
    std::thread(&ScheduleLoop::loop, this).detach();
}

void ScheduleLoop::addTask(std::function<void()> task) {
    always.push_back(task);
}

void ScheduleLoop::addConditionalTask(std::function<bool()> condition, std::function<void()> task) {
    conditionalTasks.push_back(std::make_pair(condition, task));
}


void ScheduleLoop::addCooldownTask(int cooldown, std::function<void()> task) {
    if (!scheduled.contains(cooldown))
        scheduled[cooldown] = std::vector<std::function<void()> >();
    scheduled[cooldown].push_back(task);
    if (!lastScheduleRun.contains(cooldown)) {
        task();
        lastScheduleRun[cooldown] = debug::getCurrentMs();
    }
}
