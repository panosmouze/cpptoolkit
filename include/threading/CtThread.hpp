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
 * @file CtThread.hpp
 * @brief CtThread class header file.
 * @date 18-01-2024
 * 
 */

#ifndef INCLUDE_CTTHREAD_HPP_
#define INCLUDE_CTTHREAD_HPP_

#include "core.hpp"

#include <thread>

/**
 * @class CtThread
 * @brief A simple C++ thread management class providing basic thread control and sleep functionality.
 * 
 * @ref FR-005-002-001
 * 
 * @details
 * The CtThread class provides a simple interface for creating and managing threads in C++.
 * The class is thread-safe and can be used in multi-threaded environments.
 * It is intended to be used as a base class for creating custom thread classes.
 * 
 */
class CtThread {
public:
    /**
     * @brief Make the thread sleep for a specified duration in milliseconds.
     * 
     * @ref FR-005-002-013
     * 
     * @param time Duration to sleep in milliseconds.
     */
    EXPORTED_API static void sleepFor(CtUInt64 time);

protected:
    /**
     * @brief Constructor for CtThread.
     * 
     * @ref FR-005-002-003
     */
    EXPORTED_API CtThread();

    /**
     * @brief Virtual destructor for CtThread.
     * 
     * @ref FR-005-002-011
     */
    EXPORTED_API virtual ~CtThread();

    /**
     * @brief Check if the thread is currently running.
     * 
     * @ref FR-005-002-004
     * @ref FR-005-002-005
     * 
     * @return True if the thread is running, CT_FALSE otherwise.
     */
    EXPORTED_API CtBool isRunning();

    /**
     * @brief Start the thread.
     * @throws CtThreadError if the thread is already running.
     * 
     * @ref FR-005-002-007
     * @ref FR-005-002-008
     * 
     */
    EXPORTED_API void start();

    /**
     * @brief Stop the thread.
     * 
     * @ref FR-005-002-009
     * @ref FR-005-002-010
     * 
     */
    EXPORTED_API void stop();

    /**
     * @brief Join the thread, waiting for it to finish.
     * 
     * @ref FR-005-002-012
     * 
     */
    EXPORTED_API virtual void join();

    /**
     * @brief Virtual function to be overridden by derived classes.
     *        Represents the main functionality of the thread.
     * 
     * @ref FR-005-002-002
     */
    EXPORTED_API virtual void loop() = 0;

protected:
    /**
     * @brief Set the running state of the thread.
     * 
     * @ref FR-005-002-006
     * 
     * @param running The running state to set.
     */
    void setRunning(CtBool running);

private:
    /**
     * @brief Run method executes main loop of each thread.
     */
    void run();

private:
    CtAtomic<CtBool> m_running;     /*!< Atomic flag indicating whether the thread is running. */
    std::thread m_thread;           /*!< The underlying thread object. */
};

#endif //INCLUDE_CTTHREAD_HPP_
