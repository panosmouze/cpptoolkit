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
 * @file ctworkerpool.cpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#include <gtest/gtest.h>
#include "cpptoolkit.hpp"

/**************************** Helper definitions ****************************/
#define POOL_SIZE           4
#define NUM_OF_TASKS        100
#define TASK_DURATION_MS    100

/********************************* Main test ********************************/

/**
 * @brief CtWorkerPoolTest01
 * 
 * @ref FR-005-004-001
 * @ref FR-005-004-002
 * @ref FR-005-004-003
 * @ref FR-005-004-004
 * @ref FR-005-004-006
 * @ref FR-005-004-007
 * 
 */
TEST(CtWorkerPool, CtWorkerPoolTest01) {
    CtWorkerPool pool(POOL_SIZE);
    CtBool flag[NUM_OF_TASKS] = {CT_FALSE};
    for (CtUInt32 idx = 0; idx < NUM_OF_TASKS; idx++) {
        pool.addTask([&flag, idx]{CtThread::sleepFor(TASK_DURATION_MS); flag[idx] = CT_TRUE;});
    }
    pool.join();
    for (CtUInt32 idx = 0; idx < NUM_OF_TASKS; idx++) {
        ASSERT_EQ(flag[idx], CT_TRUE);
    }
}

/**
 * @brief CtWorkerPoolTest02
 * 
 * @ref FR-005-004-005
 * 
 */
TEST(CtWorkerPool, CtWorkerPoolTest02) {
    CtBool flag[NUM_OF_TASKS] = {CT_FALSE};
    {
        CtWorkerPool pool(POOL_SIZE);
        for (CtUInt32 idx = 0; idx < NUM_OF_TASKS; idx++) {
            pool.addTask([&flag, idx]{CtThread::sleepFor(TASK_DURATION_MS); flag[idx] = CT_TRUE;});
        }
    }
    for (CtUInt32 idx = 0; idx < NUM_OF_TASKS; idx++) {
        ASSERT_EQ(flag[idx], CT_TRUE);
    }
}
