/*
 * CtFileSink.hpp
 *
 *  Created on: Jan 10, 2024
 *      Author: Mouzenidis Panagiotis
 */

#ifndef INCLUDE_IO_CTFILESINK_HPP_
#define INCLUDE_IO_CTFILESINK_HPP_

#include "definitions.hpp"
#include "io/sinks/CtSink.hpp"

#include "exceptions/CtFileError.hpp"

#include <fstream>
#include <sstream>

/**
 * @brief Represents a file-based sink for logging messages.
 *
 * This class extends CtSink and provides functionality to write log entries to a file.
 */
class CtFileSink : public CtSink {
public:
    /**
     * @brief Constructs a CtFileSink object with the specified log file name.
     *
     * @param logFileName The name of the log file.
     */
    EXPORTED_API CtFileSink(const std::string& logFileName);

    /**
     * @brief Destructor for CtFileSink.
     *
     * Closes the log file stream.
     */
    EXPORTED_API ~CtFileSink();

    /**
     * @brief Writes a log entry to the file.
     *
     * @param logEntry The log entry to be written.
     */
    EXPORTED_API void write(std::string logEntry) override;

private:
    std::ofstream m_logFile; ///< Log file stream.
};

#endif //INCLUDE_IO_CTFILESINK_HPP_
