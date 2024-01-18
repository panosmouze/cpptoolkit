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
 * @file CtSink.hpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#ifndef INCLUDE_CTSINK_HPP_
#define INCLUDE_CTSINK_HPP_

#include "definitions.hpp"
#include <mutex>

/**
 * @brief Abstract base class representing a sink for log entries.
 *
 * This class provides an interface for log sinks and includes basic synchronization mechanisms.
 */
class CtSink {
public:
    /**
     * @brief Writes a log entry to the sink.
     *
     * This method must be implemented by derived classes to handle log entry writing.
     *
     * @param logEntry The log entry to be written.
     */
    EXPORTED_API virtual void write(std::string logEntry) = 0;

protected:
    /**
     * @brief Constructor for CtSink.
     *
     * Initializes the CtSink object.
     */
    EXPORTED_API CtSink();

    /**
     * @brief Virtual destructor for CtSink.
     *
     * Ensures proper cleanup in derived classes.
     */
    EXPORTED_API virtual ~CtSink();

    /**
     * @brief Locks the internal mutex for thread-safe operations.
     */
    void lock();

    /**
     * @brief Unlocks the internal mutex.
     */
    void unlock();

private:
    std::mutex m_mtx_control; ///< Internal mutex for synchronization.
};

#endif //INCLUDE_CTSINK_HPP_
