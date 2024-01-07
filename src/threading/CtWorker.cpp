/*
 * CtWorker.cpp
 *
 *  Created on: Nov 12, 2023
 *      Author: Mouzenidis Panagiotis
 */

#include "threading/CtWorker.hpp"
#include "utils/CtTask.hpp"
#include "exceptions/CtWorkerError.hpp"

CtWorker::CtWorker() : m_running(false) {
}

CtWorker::~CtWorker() {
}

bool CtWorker::isRunning() {
    return m_running.load();
}

void CtWorker::setRunning(bool running) {
    return m_running.store(running);
}

void CtWorker::setTask(CtTask& task, std::function<void()> callback) {
    alreadyRunningCheck();
    m_task = task;
    m_callback = callback;
}

void CtWorker::runTask() {
    alreadyRunningCheck();
    setRunning(true);
    m_thread = std::thread([this]{
        m_task.getTaskFunc()();
        m_task.getCallbackFunc()();
        m_callback();
        setRunning(false);
    });
}

void CtWorker::joinTask() {
    if (m_thread.joinable()) {
        m_thread.join();
    }
}

void CtWorker::alreadyRunningCheck() {
    if (isRunning()) throw CtWorkerError("CtWorker already running.");
    joinTask();
}
