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
 * @file CtService.cpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#include "threading/CtService.hpp"

CtUInt32 CtService::m_slot_time = 10;

CtService::CtService(CtUInt64 nslots, const CtTask& task) : m_nslots(nslots), m_skip_ctr(0), m_exec_ctr(1) {
    m_worker.setTask(task);
}

CtService::~CtService() {
    stopService();
}

void CtService::runService() {
    try {
        start();
    } catch(const CtThreadError& e) {
        throw CtServiceError("Service is already running.");
    }
}

void CtService::stopService() {
    stop();
    m_worker.joinTask();
}

float CtService::getIntervalValidity() {
    return m_skip_ctr/(float)m_exec_ctr;
}

void CtService::loop() {
    try {
        m_worker.runTask();
    } catch(const CtWorkerError& e) {
        /* 
         * Service interval is smaller than the task runtime. The worker 
         * is still running while it is time to run again.
         * Exception cannot be thrown at this point because this is 
         * a thread running. The "controller" of this thread could not 
         * catch this exception.
         */
        m_skip_ctr += 1;
    }
    m_exec_ctr += 1;
    CtThread::sleepFor(m_nslots*m_slot_time);
}
