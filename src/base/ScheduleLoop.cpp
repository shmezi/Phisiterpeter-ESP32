//
// Created by Ezra Golombek on 02/12/2025.
//

#include "base/ScheduleLoop.h"

#include <algorithm>
#include <thread>

#include "Utils.h"


void ScheduleLoop::evaluateAndRunCooldown(const int &cooldown, std::chrono::milliseconds &lastRun) {
    const auto currentTime = debug::getCurrentMs();

    if ((currentTime - lastRun).count() >= cooldown) {
        for (const auto &function: scheduled[cooldown]) {
            function();
        }
        lastScheduleRun[cooldown] = currentTime;
    }
}


void ScheduleLoop::loop() {
    for (const auto &[condition, task]: conditionalTasks) {
        if (condition()) {
            task();
        }
    }
    for (const auto &task: always) {
        task();
    }
    for (auto &[cooldown, lastRun]: lastScheduleRun) {
        evaluateAndRunCooldown(cooldown, lastRun);
    }
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void ScheduleLoop::startEvent(int param) {
    std::string event = "start";
    if (param == -1)
        event = "stop";

    for (const auto &task: startFunc[event]) {
        task(param);
    }
}

static ScheduleLoop *instance;

ScheduleLoop *ScheduleLoop::getInstance() {
    if (instance == nullptr) {
        instance = new ScheduleLoop();
    }
    return instance;
}


ScheduleLoop::ScheduleLoop() {
    start();
}

void ScheduleLoop::stop() {
    active = false;
}

void ScheduleLoop::start() {
    active = true;
}

void ScheduleLoop::onEventListener(const std::string &id, std::function<void(int)> task) {
    if (!startFunc.contains(id))
        startFunc[id] = std::vector<std::function<void(int)> >();
    startFunc[id].emplace_back(task);
}

void ScheduleLoop::addTask(const std::function<void()> &task) {
    always.push_back(task);
}

void ScheduleLoop::addConditionalTask(const std::function<bool()> &condition, std::function<void()> task) {
    conditionalTasks.emplace_back(condition, task);
}


void ScheduleLoop::addCooldownTask(int cooldown, const std::function<void()> &task) {
    if (!scheduled.contains(cooldown))
        scheduled[cooldown] = std::vector<std::function<void()> >();
    scheduled[cooldown].push_back(task);
    if (!lastScheduleRun.contains(cooldown)) {
        task();
        lastScheduleRun[cooldown] = debug::getCurrentMs();
    }
}
