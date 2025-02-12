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
 * @file CtLogger.cpp
 * @brief 
 * @date 10-03-2024
 * 
 */

#include "utils/CtLogger.hpp"

CtLogger::CtLogger(CtLogger::Level level, const CtString& componentName) : m_level(level), m_componentName(componentName) {
}

CtLogger::~CtLogger() {
}

void CtLogger::log_debug(const CtString& message) {
    log(CtLogger::Level::DEBUG, message);
}

void CtLogger::log_info(const CtString& message) {
    log(CtLogger::Level::INFO, message);
}

void CtLogger::log_warning(const CtString& message) {
    log(CtLogger::Level::WARNING, message);
}

void CtLogger::log_error(const CtString& message) {
    log(CtLogger::Level::ERROR, message);
}

void CtLogger::log_critical(const CtString& message) {
    log(CtLogger::Level::CRITICAL, message);
}

void CtLogger::log(CtLogger::Level level, const CtString& message) {
    std::scoped_lock lock(m_mtx_control);
    if (level >= m_level) {
        CtString logEntry = generateLoggerMsg(level, m_componentName, message);
        std::cout << logEntry << std::endl;
    }
}

const CtString CtLogger::generateLoggerMsg(CtLogger::Level level, const CtString& componentName, const CtString& message) {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream timestamp;
    timestamp << std::put_time(std::localtime(&now_c), "%Y-%m-%d %X");

    return CtString("[" + timestamp.str() + "] [" + levelToString(level) + "] " + componentName + ": " + message);
}

const CtString CtLogger::levelToString(CtLogger::Level level) {
    CtString levelStr;
    switch (level) {
        case CtLogger::Level::DEBUG:
            levelStr = "DEBUG";
            break;
        case CtLogger::Level::INFO:
            levelStr = "INFO";
            break;
        case CtLogger::Level::WARNING:
            levelStr = "WARNING";
            break;
        case CtLogger::Level::ERROR:
            levelStr = "ERROR";
            break;
        case CtLogger::Level::CRITICAL:
            levelStr = "CRITICAL";
            break;
        default:
            levelStr = "DEBUG";
            break;
    }

    return levelStr;
}
