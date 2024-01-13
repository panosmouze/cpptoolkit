/*
 * CtThread.hpp
 *
 *  Created on: Nov 12, 2023
 *      Author: Mouzenidis Panagiotis
 */

#ifndef INCLUDE_THREADING_CTTHREAD_HPP_
#define INCLUDE_THREADING_CTTHREAD_HPP_

#include "definitions.hpp"
#include "exceptions/CtThreadError.hpp"

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

private:
    /**
     * @brief Set the running state of the thread.
     * @param running The running state to set.
     */
    void setRunning(bool running);

    /**
     * @brief Run method executes main loop of each thread.
     */
    EXPORTED_API void run();

private:
    std::atomic<bool> m_running; ///< Atomic flag indicating whether the thread is running.
    std::thread m_thread; ///< The underlying thread object.
};

#endif /* INCLUDE_THREADING_CTTHREAD_HPP_ */
