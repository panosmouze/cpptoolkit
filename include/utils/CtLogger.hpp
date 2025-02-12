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
 * @file CtLogger.hpp
 * @brief CtLogger class header file.
 * @date 10-03-2024
 * 
 */

#ifndef INCLUDE_CTLOGGER_HPP_
#define INCLUDE_CTLOGGER_HPP_

#include "core.hpp"

#include "io/CtFileOutput.hpp"

#include <iomanip>
#include <chrono>
#include <iostream>

/**
 * @brief A simple logger with log levels and timestamp.
 * 
 * @details
 * The CtLogger class provides a mechanism for logging messages with different log levels.
 * The log levels are DEBUG, INFO, WARNING, ERROR, and CRITICAL and can be used to filter messages.
 * The logger also provides a timestamp for each message. It is thread-safe and can be used in multi-threaded environments.
 */
class CtLogger {
public:
    /**
     * @brief Enum representing log levels.
     * 
     * @ref FR-004-002-003
     */
    enum class Level { DEBUG, INFO, WARNING, ERROR, CRITICAL };

    /**
     * @brief Constructs a CtLogger with a component name.
     * 
     * @ref FR-004-002-001
     * 
     * @param level The selected level given as CtLogger::Level. All messages that have level above or equal to this value will be logged.
     * @param componentName The name of the component or module.
     */
    EXPORTED_API explicit CtLogger(CtLogger::Level level = CtLogger::Level::DEBUG, const CtString& componentName = "");

    /**
     * @brief Destructor.
     * 
     * @ref FR-004-002-002
     */
    EXPORTED_API ~CtLogger();

    /**
     * @brief Log a message with debug log level.
     * 
     * @ref FR-004-002-004
     * 
     * @param message The log message.
     */
    EXPORTED_API void log_debug(const CtString& message);

    /**
     * @brief Log a message with info log level.
     * 
     * @ref FR-004-002-004
     * 
     * @param message The log message.
     */
    EXPORTED_API void log_info(const CtString& message);

    /**
     * @brief Log a message with warning log level.
     * 
     * @ref FR-004-002-004
     * 
     * @param message The log message.
     */
    EXPORTED_API void log_warning(const CtString& message);

    /**
     * @brief Log a message with error log level.
     * 
     * @ref FR-004-002-004
     * 
     * @param message The log message.
     */
    EXPORTED_API void log_error(const CtString& message);

    /**
     * @brief Log a message with critical log level.
     * 
     * @ref FR-004-002-004
     * 
     * @param message The log message.
     */
    EXPORTED_API void log_critical(const CtString& message);

private:
    /**
     * @brief Log a message with the specified log level.
     * 
     * @ref FR-004-002-004
     * @ref FR-004-002-005
     * 
     * @param level The log level.
     * @param componentName The name of the component or module.
     * @param message The log message.
     */
    void log(CtLogger::Level level, const CtString& message);

    /**
     * @brief Given the logger output level in enum CtLogger::Level format this method returns it in a string format.
     * 
     * @ref FR-004-002-005
     * 
     * @param level The level in enum CtLogger::Level format.
     * @return CtString The level in string format.
     */
    static const CtString levelToString(CtLogger::Level level);

    /**
     * @brief This method generates the message to be printed via logger.
     * 
     * @ref FR-004-002-005
     * 
     * @param level The level of the message.
     * @param component_name The component's name.
     * @param message The message.
     * @return const CtString The generated message to be printed via logger.
     */
    static const CtString generateLoggerMsg(CtLogger::Level level, const CtString& component_name, const CtString& message);

private:
    CtMutex m_mtx_control;                          /*!< Mutex for controlling access to shared resources. */
    CtLogger::Level m_level;                        /*!< Level of message logging. */
    CtString m_componentName;                       /*!< Component name. */
};

#endif //INCLUDE_CTLOGGER_HPP_