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
 * @file cttimer.cpp
 * @brief 
 * @date 06-02-2025
 * 
 */

#include <gtest/gtest.h>
#include "cpptoolkit.hpp"

/**************************** Helper definitions ****************************/

/********************************* Main test ********************************/

/**
 * @brief CtTimerTest01
 * 
 * @ref FR-003-001-001
 * @ref FR-003-001-002
 * @ref FR-003-001-003
 * @ref FR-003-001-004
 * @ref FR-005-002-013
 * 
 */
TEST(CtTimer, CtTimerTest01) {
    CtTimer timer;
    timer.tic();
    CtThread::sleepFor(1000);
    CtUInt64 elapsed = timer.toc();
    ASSERT_GE(elapsed, 1000);
    ASSERT_LE(elapsed, 1050);
}
