/*
 * CtThread.cpp
 *
 *  Created on: Nov 12, 2023
 *      Author: Mouzenidis Panagiotis
 */

#include "threading/CtThread.hpp"

#include <chrono>
#include <thread>

CtThread::CtThread() : m_running(false) {

}

CtThread::~CtThread() {
    stop();
}

void CtThread::run() {
    while(isRunning()) {
        loop();
    }
}

void CtThread::start() {
    if (!isRunning()) {
        setRunning(true);
        m_thread = std::thread(&CtThread::run, this);
    } else {
        throw CtThreadError("");
    }
}

void CtThread::stop() {
    setRunning(false);
    if (m_thread.joinable()) {
        m_thread.join();
    }
}

void CtThread::join() {
    if (m_thread.joinable()) {
        m_thread.join();
    }
}

bool CtThread::isRunning() {
    return m_running.load();
}

void CtThread::setRunning(bool running) {
    m_running.store(running);
}

void CtThread::sleepFor(uint64_t time) {
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}
