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
 * @file CtServicePool.cpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#include "threading/CtServicePool.hpp"

CtServicePool::CtServicePool(CtUInt32 nworkers) : m_nworkers(nworkers), m_worker_pool(m_nworkers) {
    m_slot_cnt = 0;
    m_exec_time = 0;
    start();
}

CtServicePool::~CtServicePool() {
    stop();
    m_worker_pool.join();
}

void CtServicePool::addTask(CtUInt32 nslots, const CtString& id, CtTask& task) {
    std::scoped_lock lock(m_mtx_control);
    m_tasks.push_back({task, id, nslots});
    try {
        start();
    } catch(const CtThreadError& e) {
    }
}

void CtServicePool::removeTask(const CtString& id) {
    std::scoped_lock lock(m_mtx_control);
    m_tasks.erase(std::remove_if(m_tasks.begin(), m_tasks.end(), 
                                    [id](CtServicePack pack) {
                                        return pack.id.compare(id) == 0; 
                                    }
                                ), m_tasks.end());
}

void CtServicePool::startServices() {
    try {
        start();
    } catch(const CtThreadError& e) {
    }
}

void CtServicePool::shutdownServices() {
    stop();
    m_worker_pool.join();
}

CtUInt32 CtServicePool::getSlotTime() {
    return CtService::m_slot_time;
}

void CtServicePool::setSlotTime(CtUInt32 slot_time) {
    CtService::m_slot_time = slot_time;
}

void CtServicePool::loop() {
    m_timer.tic();
    {
        std::scoped_lock lock(m_mtx_control);
        if (m_tasks.size() == 0) {
            return;
        } else {
            for (const CtServicePack& pack : m_tasks) {
                if (m_slot_cnt % pack.nslots == 0) {
                    m_worker_pool.addTask(pack.task);
                }
            }
        }
    }
    m_slot_cnt++;
    if (!isRunning()) return;
    m_exec_time = CtService::m_slot_time - m_timer.toc();
    if (m_exec_time > 0) {
        CtThread::sleepFor(m_exec_time);
    }
}
