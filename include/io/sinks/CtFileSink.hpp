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
 * @file CtFileSink.hpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#ifndef INCLUDE_CTFILESINK_HPP_
#define INCLUDE_CTFILESINK_HPP_

#include "definitions.hpp"
#include "io/sinks/CtSink.hpp"

#include "exceptions/CtFileExceptions.hpp"

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
     * @brief Enum representing write mode.
     */
    enum class WriteMode { Append, Truncate };

    /**
     * @brief Constructs a CtFileSink object with the specified log file name.
     *
     * @param logFileName The name of the log file.
     */
    EXPORTED_API CtFileSink(const std::string& logFileName, WriteMode mode = WriteMode::Append);

    /**
     * @brief Destructor for CtFileSink.
     *
     * Closes the log file stream.
     */
    EXPORTED_API ~CtFileSink();

    /**
     * @brief Writes a log entry to the file.
     *
     * @param msg The log entry to be written.
     */
    EXPORTED_API void write(const std::string& msg) override;

private:
    std::ofstream m_logFile; ///< Log file stream.
    CtFileSink::WriteMode m_mode; ///< Mode opening the stream.
};

#endif //INCLUDE_CTFILESINK_HPP_
