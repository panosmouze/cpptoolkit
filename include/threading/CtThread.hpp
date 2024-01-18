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
 * @brief 
 * @date 18-01-2024
 * 
 */

#ifndef INCLUDE_CTTHREAD_HPP_
#define INCLUDE_CTTHREAD_HPP_

#include "definitions.hpp"

#include <thread>
#include <atomic>

/**
 * @class CtThread
 * @brief A simple C++ thread management class providing basic thread control and sleep functionality.
 */
class CtThread {
public:
    /**
     * @brief Make the thread sleep for a specified duration in milliseconds.
     * @param time Duration to sleep in milliseconds.
     */
    EXPORTED_API static void sleepFor(uint64_t time);

protected:
    /**
     * @brief Constructor for CtThread.
     */
    EXPORTED_API CtThread();

    /**
     * @brief Virtual destructor for CtThread.
     */
    EXPORTED_API virtual ~CtThread();

    /**
     * @brief Check if the thread is currently running.
     * @return True if the thread is running, false otherwise.
     */
    EXPORTED_API bool isRunning();

    /**
     * @brief Start the thread.
     * @throws CtThreadError if the thread is already running.
     */
    EXPORTED_API void start();

    /**
     * @brief Stop the thread.
     */
    EXPORTED_API void stop();

    /**
     * @brief Join the thread, waiting for it to finish.
     */
    EXPORTED_API void join();

    /**
     * @brief Virtual function to be overridden by derived classes.
     *        Represents the main functionality of the thread.
     */
    EXPORTED_API virtual void loop() = 0;

protected:
    /**
     * @brief Set the running state of the thread.
     * @param running The running state to set.
     */
    void setRunning(bool running);

private:
    /**
     * @brief Run method executes main loop of each thread.
     */
    void run();

private:
    std::atomic<bool> m_running; ///< Atomic flag indicating whether the thread is running.
    std::thread m_thread; ///< The underlying thread object.
};

#endif //INCLUDE_CTTHREAD_HPP_
