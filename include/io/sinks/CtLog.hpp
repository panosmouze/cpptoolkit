/*
 * CtLog.hpp
 *
 *  Created on: Jan 10, 2023
 *      Author: Mouzenidis Panagiotis
 */

#ifndef INCLUDE_IO_CTLOG_HPP_
#define INCLUDE_IO_CTLOG_HPP_

#include "definitions.hpp"
#include "io/sinks/CtSink.hpp"

/**
 * @brief Represents a simple logging sink.
 *
 * This class extends CtSink and provides a basic implementation for writing log entries.
 */
class CtLog : public CtSink {
public:
    /**
     * @brief Constructs a CtLog object.
     *
     * Initializes the CtLog object.
     */
    EXPORTED_API CtLog();

    /**
     * @brief Destructor for CtLog.
     *
     * Performs any necessary cleanup.
     */
    EXPORTED_API ~CtLog();

    /**
     * @brief Writes a log entry.
     *
     * @param logEntry The log entry to be written.
     */
    EXPORTED_API void write(std::string logEntry) override;
};

#endif //INCLUDE_IO_CTLOG_HPP_
