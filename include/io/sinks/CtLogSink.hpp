/*
 * CtLogSink.hpp
 *
 *  Created on: Jan 10, 2023
 *      Author: Mouzenidis Panagiotis
 */

#ifndef INCLUDE_IO_CTLOGSINK_HPP_
#define INCLUDE_IO_CTLOGSINK_HPP_

#include "definitions.hpp"
#include "io/sinks/CtSink.hpp"

/**
 * @brief Represents a simple logging sink.
 *
 * This class extends CtSink and provides a basic implementation for writing log entries.
 */
class CtLogSink : public CtSink {
public:
    /**
     * @brief Constructs a CtLogSink object.
     *
     * Initializes the CtLogSink object.
     */
    EXPORTED_API CtLogSink();

    /**
     * @brief Destructor for CtLog.
     *
     * Performs any necessary cleanup.
     */
    EXPORTED_API ~CtLogSink();

    /**
     * @brief Writes a log entry.
     *
     * @param logEntry The log entry to be written.
     */
    EXPORTED_API void write(std::string logEntry) override;
};

#endif //INCLUDE_IO_CTLOGSINK_HPP_
