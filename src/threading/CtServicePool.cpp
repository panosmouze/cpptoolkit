/*
 * CtServicePool.cpp
 *
 *  Created on: Nov 13, 2023
 *      Author: Mouzenidis Panagiotis
 */

#include "threading/CtServicePool.hpp"
#include "exceptions/CtServiceError.hpp"

CtServicePool::CtServicePool(uint32_t nworkers) : m_nworkers(nworkers), m_worker_pool(m_nworkers) {
    start();
}

CtServicePool::~CtServicePool() {
    stop();
    m_worker_pool.join();
}

void CtServicePool::addTask(uint32_t nslots, std::string id, CtTask& task) {
    std::scoped_lock lock(m_mtx_control);
    if (nslots >= 0) {
        m_tasks.push_back({task, id, nslots});
        try {
            start();
        } catch(CtThreadError& e) {
        }
    } else {
        throw CtServiceError("Invalid interval_slot number (should be >0).");
    }
}

void CtServicePool::removeTask(std::string id) {
    std::scoped_lock lock(m_mtx_control);
    m_tasks.erase(std::remove_if(m_tasks.begin(), m_tasks.end(), [id](CtServicePack pack) {return pack.id.compare(id) == 0; }), m_tasks.end());
}

void CtServicePool::startServices() {
    try {
        start();
    } catch(CtThreadError& e) {
    }
}

void CtServicePool::shutdownServices() {
    stop();
    m_worker_pool.join();
}

uint32_t CtServicePool::getSlotTime() {
    return CtService::m_slot_time;
}

void CtServicePool::setSlotTime(uint32_t slot_time) {
    CtService::m_slot_time = slot_time;
}

void CtServicePool::loop() {
    m_timer.tic();
    {
        std::scoped_lock lock(m_mtx_control);
        if (m_tasks.size() == 0) {
            return;
        } else {
            for (CtServicePack& pack : m_tasks) {
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
