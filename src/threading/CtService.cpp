/*
 * CtService.cpp
 *
 *  Created on: Nov 13, 2023
 *      Author: Mouzenidis Panagiotis
 */

#include "threading/CtService.hpp"
#include "exceptions/CtWorkerError.hpp"

uint32_t CtService::m_slot_time = 10;

CtService::CtService(uint64_t nslots, CtTask& task) : m_nslots(nslots){
    m_worker.setTask(task);
    runService();
}

CtService::~CtService() {
    stopService();
}

void CtService::runService() {
    try {
        start();
    } catch(CtThreadError& e) {

    }
}

void CtService::stopService() {
    stop();
    m_worker.joinTask();
}

void CtService::loop() {
    try {
        m_worker.runTask();
    } catch(CtWorkerError& e) {

    }
    CtThread::sleepFor(m_nslots*m_slot_time);
}
