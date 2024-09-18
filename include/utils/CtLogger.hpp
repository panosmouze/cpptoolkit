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
 * @brief 
 * @date 10-03-2024
 * 
 */

#ifndef INCLUDE_CTLOGGER_HPP_
#define INCLUDE_CTLOGGER_HPP_

#include "definitions.hpp"
#include "io/CtFileOutput.hpp"

#include <string>
#include <iomanip>
#include <chrono>
#include <vector>
#include <iostream>

/**
 * @brief A simple logger with log levels and timestamp.
 */
class CtLogger {
public:
    /**
     * @brief Enum representing log levels.
     */
    enum class Level { DEBUG, INFO, WARNING, ERROR, CRITICAL };

    /**
     * @brief Constructs a CtLogger with a component name.
     * 
     * @param level The selected level given as CtLogger::Level. All messages that have level above or equal to this value will be logged.
     * @param componentName The name of the component or module.
     */
    EXPORTED_API explicit CtLogger(CtLogger::Level level = CtLogger::Level::DEBUG, const std::string& componentName = "");

    /**
     * @brief Destructor.
     */
    EXPORTED_API ~CtLogger();

    /**
     * @brief Log a message with debug log level.
     * 
     * @param message The log message.
     */
    EXPORTED_API void log_debug(const std::string& message);

    /**
     * @brief Log a message with info log level.
     * 
     * @param message The log message.
     */
    EXPORTED_API void log_info(const std::string& message);

    /**
     * @brief Log a message with warning log level.
     * 
     * @param message The log message.
     */
    EXPORTED_API void log_warning(const std::string& message);

    /**
     * @brief Log a message with error log level.
     * 
     * @param message The log message.
     */
    EXPORTED_API void log_error(const std::string& message);

    /**
     * @brief Log a message with critical log level.
     * 
     * @param message The log message.
     */
    EXPORTED_API void log_critical(const std::string& message);

    /**
     * @brief Given the logger output level in string format this method returns the enum CtLogger::Level format.
     * 
     * @param level_str The level in string format.
     * @return CtLogger::Level The level in enum format.
     */
    EXPORTED_API static CtLogger::Level stringToLevel(const std::string& level_str);

private:
    /**
     * @brief Log a message with the specified log level.
     * @param level The log level.
     * @param componentName The name of the component or module.
     * @param message The log message.
     */
    void log(CtLogger::Level level, const std::string& message);

    /**
     * @brief Given the logger output level in enum CtLogger::Level format this method returns it in a string format.
     * 
     * @param level The level in enum CtLogger::Level format.
     * @return std::string The level in string format.
     */
    static const std::string levelToString(CtLogger::Level level);

    /**
     * @brief This method generates the message to be printed via logger.
     * 
     * @param level The level of the message.
     * @param component_name The component's name.
     * @param message The message.
     * @return const std::string The generated message to be printed via logger.
     */
    static const std::string generateLoggerMsg(CtLogger::Level level, const std::string& component_name, const std::string& message);

private:
    CtLogger::Level m_level; ///< Level of message logging.
    std::string m_componentName; ///< Component name.
    bool m_verbose; ///< Print to terminal or not.
};

#endif //INCLUDE_CTLOGGER_HPP_