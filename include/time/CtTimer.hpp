/*
 * CtTimer.hpp
 *
 *  Created on: Nov 12, 2023
 *      Author: Mouzenidis Panagiotis
 */

#ifndef INCLUDE_TIME_CTTIMER_HPP_
#define INCLUDE_TIME_CTTIMER_HPP_

#include "definitions.hpp"
#include <chrono>

/**
 * @class CtTimer
 * @brief Simple timer utility using std::chrono for high-resolution timing.
 */
class CtTimer {
public:
    /**
     * @brief Constructor for CtTimer.
     */
    EXPORTED_API CtTimer();

    /**
     * @brief Destructor for CtTimer.
     */
    EXPORTED_API ~CtTimer();

    /**
     * @brief Record the current time as a reference point.
     */
    EXPORTED_API void tic();

    /**
     * @brief Measure the elapsed time since the last call to tic().
     * @return Elapsed time in milliseconds.
     */
    EXPORTED_API uint64_t toc();

    /**
     * @brief Get the current time in milliseconds.
     * @return Current time in milliseconds.
     */
    EXPORTED_API static uint64_t current();

    /**
     * @brief Convert time from milliseconds to nanoseconds.
     * @param time Time value in milliseconds.
     * @return Time value converted to nanoseconds.
     */
    EXPORTED_API static uint64_t millisToNano(uint64_t time);

private:
    uint64_t m_reference; ///< Reference time for measuring elapsed time.
};

#endif /* INCLUDE_TIME_CTTIMER_HPP_ */
