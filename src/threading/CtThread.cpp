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
 * @file CtThread.cpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#include "threading/CtThread.hpp"

#include <chrono>

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
        join();
        setRunning(true);
        m_thread = std::thread(&CtThread::run, this);
    } else {
        throw CtThreadError("Thread already running.");
    }
}

void CtThread::stop() {
    setRunning(false);
    CtThread::join();
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

void CtThread::sleepFor(CtUInt64 time) {
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}
