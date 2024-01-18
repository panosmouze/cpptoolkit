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
 * @file CtFileSink.cpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#include "io/sinks/CtFileSink.hpp"

CtFileSink::CtFileSink(const std::string& logFileName) : CtSink() {
    try {
        m_logFile.open(logFileName, std::ios::out | std::ios::app);
    } catch (...) {
        throw CtFileWriteError("");
    }
}

CtFileSink::~CtFileSink() {
    if (m_logFile.is_open()) {
        m_logFile.close();
    }
}

void CtFileSink::write(std::string logEntry) {
    lock();
    if (m_logFile.is_open()) {
        m_logFile << logEntry << std::endl;
    }
    unlock();
}
