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
