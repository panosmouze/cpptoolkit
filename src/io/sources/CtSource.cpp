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
 * @file CtSource.cpp
 * @brief 
 * @date 31-01-2024
 * 
 */

#include "io/sources/CtSource.hpp"

CtSource::CtSource() {
    registerEvent((uint8_t)CtSourceEvent::Avail);
    registerEvent((uint8_t)CtSourceEvent::Eof);
}

CtSource::~CtSource() {

}

void CtSource::start() {
    CtThread::start();
}

void CtSource::stop() {
    CtThread::stop();
}

void CtSource::join() {
    CtThread::join();
    CtObject::waitPendingEvents();
}

void CtSource::setOutType(CtDataType p_type) {
    m_outType = p_type;
}

bool CtSource::acceptOutType(CtDataType p_type) {
    return (p_type == m_outType);
}

CtData* CtSource::get() {
    std::scoped_lock lock(m_mtx_control);
    CtData* data = nullptr;
    if (m_queue.size() > 0) {
        data = m_queue.front();
        m_queue.pop();
    }
    return data;
}

void CtSource::set(CtData* data) {
    std::scoped_lock lock(m_mtx_control);
    m_queue.push(data);
}
