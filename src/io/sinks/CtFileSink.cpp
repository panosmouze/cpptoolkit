/*
 * CtFileSink.cpp
 *
 *  Created on: Jan 10, 2023
 *      Author: Mouzenidis Panagiotis
 */
#include "io/sinks/CtFileSink.hpp"

CtFileSink::CtFileSink(const std::string& logFileName) : CtSink() {
    try {
        m_logFile.open(logFileName, std::ios::out | std::ios::app);
    } catch (...) {
        throw CtFileError("");
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