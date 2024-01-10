/*
 * CtFile.cpp
 *
 *  Created on: Jan 10, 2023
 *      Author: Mouzenidis Panagiotis
 */
#include "io/sinks/CtFile.hpp"

CtFile::CtFile(const std::string& logFileName) : CtSink() {
    try {
        m_logFile.open(logFileName, std::ios::out | std::ios::app);
    } catch (...) {
        throw CtFileError("");
    }
}

CtFile::~CtFile() {
    if (m_logFile.is_open()) {
        m_logFile.close();
    }
}

void CtFile::write(std::string logEntry) {
    lock();
    if (m_logFile.is_open()) {
        m_logFile << logEntry << std::endl;
    }
    unlock();
}