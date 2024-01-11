/*
 * CtLogger.cpp
 *
 *  Created on: Nov 13, 2023
 *      Author: Mouzenidis Panagiotis
 */

#include "io/CtLogger.hpp"
#include "exceptions/CtFileError.hpp"

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

        for (CtSink* sink: m_sinks) {
            sink->write(logEntry);
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