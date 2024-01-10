/*
 * CtSink.hpp
 *
 *  Created on: Jan 10, 2023
 *      Author: Mouzenidis Panagiotis
 */

#ifndef INCLUDE_IO_CTSINK_HPP_
#define INCLUDE_IO_CTSINK_HPP_

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

#endif //INCLUDE_IO_CTSINK_HPP_
