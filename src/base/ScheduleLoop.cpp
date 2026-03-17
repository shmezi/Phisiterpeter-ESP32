//
// Created by Ezra Golombek on 02/12/2025.
//

#include "base/ScheduleLoop.h"

#include <algorithm>
#include <thread>

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


void ScheduleLoop::loop() {
    // ---------------- Conditional Tasks ----------------
    for (size_t i = 0; i < conditionalTasks.size(); i++) {
        auto it = conditionalTasks.begin();
        std::advance(it, i);

        auto condition = it->first;
        auto task = it->second;

        if (!task) continue;
        if (condition()) {
            task();
        }
    }

    // ---------------- Always Tasks ----------------
    for (size_t i = 0; i < always.size(); i++) {
        auto task = always[i];
        if (!task) continue;
        task();
    }
    // for (size_t i = 0; i < queuedIDTasks.size(); i++) {
    //     auto taskID = queuedIDTasks.front();
    //     auto task = idToTask[taskID];
    //     if (task)
    //         task();
    //     else
    //         debug::warn("Tried to run task id: " + std::to_string(taskID) + " But it was null!");
    //     debug::log("Ran task id: " + std::to_string(taskID));
    //     queuedIDTasks.pop_front();
    // }


    // ---------------- Last Schedule Run ----------------
    for (size_t i = 0; i < lastScheduleRun.size(); i++) {
        auto it = lastScheduleRun.begin();
        std::advance(it, i);

        auto cooldown = it->first;
        auto &lastRun = it->second;

        evaluateAndRunCooldown(cooldown, lastRun);
    }

    // ---------------- Delayed Tasks ----------------
    std::vector<std::function<void()> > tasksToRun;
    std::vector<int> keysToRemove;

    std::vector<int> delayedKeys;
    delayedKeys.reserve(delayedTask.size());
    for (auto &pair: delayedTask) {
        delayedKeys.push_back(pair.first);
    }

    for (size_t i = 0; i < delayedKeys.size(); i++) {
        int timeToRunTasks = delayedKeys[i];
        auto &tasks = delayedTask[timeToRunTasks];

        if (debug::getCurrentMs().count() - timeToRunTasks < 0) continue;

        keysToRemove.push_back(timeToRunTasks);

        for (size_t j = 0; j < tasks.size(); j++) {
            auto task = tasks[j];
            if (!task) continue;
            tasksToRun.push_back(task);
        }
    }

    for (size_t i = 0; i < keysToRemove.size(); i++) {
        delayedTask.erase(keysToRemove[i]);
    }

    for (size_t i = 0; i < tasksToRun.size(); i++) {
        auto task = tasksToRun[i];
        if (!task) continue;
        task();
    }

    // ---------------- Sleep ----------------
}

void ScheduleLoop::startEvent(int param) {
    std::string event = "start";
    if (param == -1)
        event = "stop";
    if (!startFunc.contains(event)) {
        debug::runTimeError("No event of id '" + event + "' found!");
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
    const auto key = debug::getCurrentMs().count() + cooldown;
    if (!delayedTask.contains(key))
        delayedTask[key] = std::vector<std::function<void()> >();
    delayedTask[key].emplace_back(task);
}

int ScheduleLoop::newIDTask(std::function<void()> task) {
    int id = idToTask.size() - 1;
    debug::log("A new task has been registered ID: " + std::to_string(id));
    idToTask[id] = task;
    return id;
}

void ScheduleLoop::queueIDTask(int id) {
    queuedIDTasks.push_back(id);
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
