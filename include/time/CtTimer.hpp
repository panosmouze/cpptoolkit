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
 * @file CtTimer.hpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#ifndef INCLUDE_CTTIMER_HPP_
#define INCLUDE_CTTIMER_HPP_

#include "definitions.hpp"
#include "CtTypes.hpp"

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

#endif //INCLUDE_CTTIMER_HPP_
