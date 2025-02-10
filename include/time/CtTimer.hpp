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
 * @brief CtTimer class header file.
 * @date 18-01-2024
 * 
 */

#ifndef INCLUDE_CTTIMER_HPP_
#define INCLUDE_CTTIMER_HPP_

#include "core.hpp"

#include <chrono>

/**
 * @class CtTimer
 * @brief Simple timer utility using std::chrono for high-resolution timing.
 * 
 * @details
 * The CtTimer class provides a simple interface for measuring elapsed time.
 * 
 * @code {.cpp}
 * CtTimer timer;
 * timer.tic();
 * // Do something
 * CtUInt64 elapsed = timer.toc();
 * std::cout << "Elapsed time: " << elapsed << " ms" << std::endl;
 * @endcode
 * 
 */
class CtTimer {
public:
    /**
     * @brief Constructor for CtTimer.
     * 
     * @ref FR-003-001-001
     */
    EXPORTED_API CtTimer();

    /**
     * @brief Destructor for CtTimer.
     * 
     * @ref FR-003-001-002
     */
    EXPORTED_API ~CtTimer();

    /**
     * @brief Record the current time as a reference point.
     * 
     * @ref FR-003-001-003
     */
    EXPORTED_API void tic();

    /**
     * @brief Measure the elapsed time since the last call to tic().
     * 
     * @ref FR-003-001-004
     * 
     * @return Elapsed time in milliseconds.
     */
    EXPORTED_API CtUInt64 toc();

    /**
     * @brief Get the current time in milliseconds.
     * 
     * @ref FR-003-001-005
     * 
     * @return Current time in milliseconds.
     */
    EXPORTED_API static CtUInt64 current();

private:
    CtUInt64 m_reference;           /*!< Reference time for measuring elapsed time. */
};

#endif //INCLUDE_CTTIMER_HPP_
