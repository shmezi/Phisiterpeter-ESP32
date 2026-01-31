//
// Created by Ezra Golombek on 02/12/2025.
//

#include "base/ScheduleLoop.h"

#include <algorithm>
#include <thread>
#include <driver/uart.h>
#include <hal/uart_types.h>

#include "Utils.h"
#include "expressions/game/functions/SendResultExpression.h"


void ScheduleLoop::evaluateAndRunCooldown(const int &cooldown, std::chrono::milliseconds &lastRun) {
    const auto currentTime = debug::getCurrentMs();

    if ((currentTime - lastRun).count() >= cooldown) {
        for (const auto &function: scheduled[cooldown]) {
            function();
        }
        lastScheduleRun[cooldown] = currentTime;
    }
}

static constexpr auto messageLimit = 300;

void messageLoop() {
    static auto lastRun = debug::getCurrentMs();
    if (debug::getCurrentMs().count() - lastRun.count() < messageLimit) return;
    for (int i = 0; i < 3; ++i) {
        if (SendResultExpression::nextMessage[i] == SendResultExpression::prevMessage[i]) continue;
        const auto cMessage = SendResultExpression::nextMessage[i].c_str();

        uart_write_bytes(UART_NUM_2, cMessage, strlen(cMessage));
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
    for (auto [timeToRunTasks, tasks]: delayedTask) {
        if (debug::getCurrentMs().count() - timeToRunTasks < 0) continue;
        for (auto task: tasks) {
            task();
        }
        delayedTask.erase(timeToRunTasks);
    }

    // messageLoop();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void ScheduleLoop::startEvent(int param) {
    std::string event = "start";
    if (param == -1)
        event = "stop";
    if (!startFunc.contains(event)) {
        debug::error("No event of id '" + event + "' found!");
        return;
    }
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
    if (!startFunc.contains(id)) {
        startFunc[id] = std::vector<std::function<void(int)> >();
        debug::log("Registered event handler with ID: " + id);
    }
    startFunc[id].emplace_back(task);
}

void ScheduleLoop::addTask(const std::function<void()> &task) {
    always.push_back(task);
}

void ScheduleLoop::addConditionalTask(const std::function<bool()> &condition, std::function<void()> task) {
    conditionalTasks.emplace_back(condition, task);
}

void ScheduleLoop::runAfterPeriod(const int &cooldown, std::function<void()> task) {
    delayedTask[debug::getCurrentMs().count() + cooldown].emplace_back(task);
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
