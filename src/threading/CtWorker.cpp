/*
MIT License

Copyright (c) 2024 Mouzenidis Panagiotis

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
 * @file CtWorker.cpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#include "threading/CtWorker.hpp"
#include "utils/CtTask.hpp"
#include "exceptions/CtThreadExceptions.hpp"

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

void CtWorker::setTask(const CtTask& task, std::function<void()> callback) {
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
    if (isRunning()) {
        throw CtWorkerError("CtWorker already running.");
    }
    joinTask();
}
