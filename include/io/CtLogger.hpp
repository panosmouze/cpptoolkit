/*
 * CtLogger.hpp
 *
 *  Created on: Nov 13, 2023
 *      Author: Mouzenidis Panagiotis
 */

#ifndef INCLUDE_IO_CTLOGGER_HPP_
#define INCLUDE_IO_CTLOGGER_HPP_

#include "definitions.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <mutex>

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
     * @brief Constructs a CtLogger with a log file name. 
     *          This constructor may throw CtFileError if there is any kind of problem with the file.
     * 
     * @param logFileName The name of the log file.
     * @param level The selected level. All messages that have level above or equal to this value will be logged.
     * @param componentName The name of the component or module.
     */
    EXPORTED_API explicit CtLogger(const std::string& logFileName, CtLogger::Level level = CtLogger::Level::DEBUG, const std::string& componentName = "");

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
    std::mutex m_mtx_control; ///< Mutex for controlling access to shared resources.
    std::ofstream m_logFile; ///< Log file stream.
    CtLogger::Level m_level; ///< Level of message logging.
    std::string m_componentName; ///< Component name.
};

#endif //INCLUDE_IO_CTLOGGER_HPP_
