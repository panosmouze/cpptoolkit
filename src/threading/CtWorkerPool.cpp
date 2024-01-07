/*
 * CtWorkerPool.cpp
 *
 *  Created on: Nov 13, 2023
 *      Author: Mouzenidis Panagiotis
 */

#include "threading/CtWorkerPool.hpp"
#include "exceptions/CtWorkerError.hpp"

CtWorkerPool::CtWorkerPool(uint32_t nworkers) : m_nworkers(nworkers), m_active_tasks(0), m_queued_tasks(0) {
    for (int idx = 0; idx < m_nworkers; idx++) {
        m_workers.push_back(std::make_unique<CtWorker>());
    }
    m_taskAssigner.setTaskFunc([this](){
        taskAssignerFunc();
    });
}

CtWorkerPool::~CtWorkerPool() {
    join();
    free();
}

void CtWorkerPool::addTask(CtTask& task) {
    std::scoped_lock lock(m_mtx_control);
    m_tasks.push(task);
    m_queued_tasks++;
    try {
        m_taskAssigner.runTask();
    } catch (CtWorkerError& e) {
    }
}

void CtWorkerPool::join() {
    bool s_breakFlag;
    do {
        m_taskAssigner.joinTask();
        s_breakFlag = (m_queued_tasks == 0) && (m_active_tasks == 0);
    } while(!s_breakFlag);
}

void CtWorkerPool::assignTask(uint32_t idx) {
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

void CtWorkerPool::taskAssignerFunc() {
    while (m_queued_tasks.load() > 0) {
        for (int idx = 0; idx < m_nworkers; idx++) {
            if (!m_workers.at(idx).get()->isRunning() && m_queued_tasks.load() != 0) {
                assignTask(idx);
            }
        }
    }
}

void CtWorkerPool::free() {
    for (int idx = 0; idx < m_nworkers; idx++) {
        m_workers.back().get()->joinTask();
        m_workers.pop_back();
    }
}
