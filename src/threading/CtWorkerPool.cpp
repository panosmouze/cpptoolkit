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
 * @file CtWorkerPool.cpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#include "threading/CtWorkerPool.hpp"
#include "exceptions/CtThreadExceptions.hpp"

CtWorkerPool::CtWorkerPool(CtUInt32 nworkers) : m_nworkers(nworkers), m_active_tasks(0), m_queued_tasks(0) {
    for (int idx = 0; idx < m_nworkers; idx++) {
        m_workers.push_back(std::make_unique<CtWorker>());
    }
}

CtWorkerPool::~CtWorkerPool() {
    CtThread::stop();
    free();
}

void CtWorkerPool::addTask(CtTask& task) {
    std::scoped_lock lock(m_mtx_control);
    m_tasks.push(task);
    m_queued_tasks++;
    try {
        start();
    } catch (const CtThreadError& e) {
    }
}

void CtWorkerPool::join() {
    CtThread::join();
}

void CtWorkerPool::assignTask(CtUInt32 idx) {
    std::scoped_lock lock(m_mtx_control);
    try {
        m_workers.at(idx).get()->setTask(m_tasks.front(), [this](){m_active_tasks--;});
        m_workers.at(idx).get()->runTask();
    } catch (CtWorkerError& e) {
        return;
    }
    m_active_tasks++;
    m_tasks.pop();
    m_queued_tasks--;
}

void CtWorkerPool::free() {
    for (int idx = 0; idx < m_nworkers; idx++) {
        m_workers.back().get()->joinTask();
        m_workers.pop_back();
    }
}

void CtWorkerPool::loop() {
    bool s_breakFlag = false;
    while (!s_breakFlag) {
        for (int idx = 0; idx < m_nworkers; idx++) {
            if (!m_workers.at(idx).get()->isRunning() && m_queued_tasks.load() != 0) {
                assignTask(idx);
            }
        }
        s_breakFlag = (m_queued_tasks.load() == 0) && (m_active_tasks.load() == 0);
    }
    setRunning(false);
}
