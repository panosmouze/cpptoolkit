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
 * @file ctservicepool.cpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#include <gtest/gtest.h>
#include "cpptoolkit.hpp"

/**************************** Helper definitions ****************************/
#define NUM_OF_SERVICES     10
#define TIME_INTERVAL       25
#define MAIN_SLEEP_MS       1100
/********************************* Main test ********************************/

/**
 * @brief CtServicePool01
 * 
 * @details
 * Test the basic functionality of CtServicePool class.
 * 
 * @ref FR-005-006-001
 * @ref FR-005-006-002
 * @ref FR-005-006-003
 * @ref FR-005-006-005
 * @ref FR-005-006-008
 * @ref FR-005-006-009
 * @ref FR-005-006-010
 * @ref FR-005-006-011
 * 
 */
TEST(CtServicePool, CtServicePool01) {
    CtServicePool pool(4);
    CtUInt8 data[NUM_OF_SERVICES] = {0};
    for (CtUInt8 idx = 0; idx < NUM_OF_SERVICES; idx++) {
        CtString id = CtString("service") + ToCtString(idx);
        pool.addTaskFunc(TIME_INTERVAL, id, [&data, idx]() {
            data[idx] += 1;
        });
    }
    pool.startServices();
    CtThread::sleepFor(MAIN_SLEEP_MS);
    pool.shutdownServices();
    for (CtUInt8 idx = 0; idx < NUM_OF_SERVICES; idx++) {
        ASSERT_LE(data[idx], 5);
    }
}

/**
 * @brief CtServicePool02
 * 
 * @details
 * Test the basic functionality of CtServicePool class.
 * 
 * @ref FR-005-006-006
 * @ref FR-005-006-007
 * 
 */
TEST(CtServicePool, CtServicePool02) {
    CtServicePool pool(4);
    CtUInt8 data[NUM_OF_SERVICES] = {0};
    for (CtUInt8 idx = 0; idx < NUM_OF_SERVICES; idx++) {
        CtString id = CtString("service") + ToCtString(idx);
        pool.addTaskFunc(TIME_INTERVAL, id, [&data, idx]() {
            data[idx] += 1;
        });
    }
    pool.startServices();
    CtThread::sleepFor(MAIN_SLEEP_MS);
    for (CtUInt8 idx = 0; idx < NUM_OF_SERVICES/2; idx++) {
        CtString id = CtString("service") + ToCtString(idx);
        pool.removeTask(id);
    }
    CtThread::sleepFor(MAIN_SLEEP_MS);
    pool.shutdownServices();
    for (CtUInt8 idx = 0; idx < NUM_OF_SERVICES/2; idx++) {
        ASSERT_LE(data[idx], 6);
    }
    for (CtUInt8 idx = NUM_OF_SERVICES/2; idx < NUM_OF_SERVICES; idx++) {
        ASSERT_LE(data[idx], 11);
    }
}

/**
 * @brief CtServicePool03
 * 
 * @details
 * Test the basic functionality of CtServicePool class.
 * 
 * @ref FR-005-006-004
 * 
 */
TEST(CtServicePool, CtServicePool03) {
    CtUInt8 data[NUM_OF_SERVICES] = {0};
    {
        CtServicePool pool(4);
        for (CtUInt8 idx = 0; idx < NUM_OF_SERVICES; idx++) {
            CtString id = CtString("service") + ToCtString(idx);
            pool.addTaskFunc(TIME_INTERVAL, id, [&data, idx]() {
                data[idx] += 1;
            });
        }
        pool.startServices();
        CtThread::sleepFor(MAIN_SLEEP_MS);
    }
    for (CtUInt8 idx = 0; idx < NUM_OF_SERVICES; idx++) {
        ASSERT_LE(data[idx], 5);
    }
}