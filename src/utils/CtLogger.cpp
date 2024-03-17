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

CtLogger::CtLogger(CtLogger::Level level, const std::string& componentName) : m_level(level), m_componentName(componentName) {
}

CtLogger::~CtLogger() {
}

void CtLogger::addSink(CtSink* sink) {
    m_sinks.push_back(sink);
}

void CtLogger::log_debug(const std::string& message) {
    log(CtLogger::Level::DEBUG, message);
}

void CtLogger::log_info(const std::string& message) {
    log(CtLogger::Level::INFO, message);
}

void CtLogger::log_warning(const std::string& message) {
    log(CtLogger::Level::WARNING, message);
}

void CtLogger::log_error(const std::string& message) {
    log(CtLogger::Level::ERROR, message);
}

void CtLogger::log_critical(const std::string& message) {
    log(CtLogger::Level::CRITICAL, message);
}

void CtLogger::log(CtLogger::Level level, const std::string& message) {
    if (level >= m_level) {
        std::string logEntry = generateLoggerMsg(level, m_componentName, message);

        for (CtSink* s_sink: m_sinks) {
            CtBlockDataPtr s_data(new CtTextData(logEntry));
            s_sink->setData({s_data});
        }
    }
}

const std::string CtLogger::generateLoggerMsg(CtLogger::Level level, const std::string& componentName, const std::string& message) {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream timestamp;
    timestamp << std::put_time(std::localtime(&now_c), "%Y-%m-%d %X");

    return std::string("[" + timestamp.str() + "] [" + levelToString(level) + "] " + componentName + ": " + message);
}

const std::string CtLogger::levelToString(CtLogger::Level level) {
    std::string levelStr;
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

CtLogger::Level CtLogger::stringToLevel(const std::string& levelStr) {
    Level level;
    if (levelStr.compare("DEBUG") == 0) {
        level = CtLogger::Level::DEBUG;
    } else if (levelStr.compare("INFO") == 0) {
        level = CtLogger::Level::INFO;
    } else if (levelStr.compare("WARNING") == 0) {
        level = CtLogger::Level::WARNING;
    } else if (levelStr.compare("ERROR") == 0) {
        level = CtLogger::Level::ERROR;
    } else if (levelStr.compare("CRITICAL") == 0) {
        level = CtLogger::Level::CRITICAL;
    } else {
        level = CtLogger::Level::DEBUG;
    }

    return level;
}
