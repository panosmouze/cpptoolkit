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
 * @file ctworker.cpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#include <gtest/gtest.h>
#include "cpptoolkit.hpp"

/**************************** Helper definitions ****************************/
#define TASK_DURATION_MS    100

/********************************* Main test ********************************/

/**
 * @brief CtWorkerTest01
 * 
 * @details
 * Test the main functionality of CtWorker methods isRunning, setTaskFunc, runTask and joinTask.
 * 
 * @ref FR-005-003-001
 * @ref FR-005-003-002
 * @ref FR-005-003-003
 * @ref FR-005-003-004
 * @ref FR-005-003-006
 * @ref FR-005-003-007
 * @ref FR-005-003-008
 * @ref FR-005-003-010
 * 
 */
TEST(CtWorker, CtWorkerTest01) {
    CtWorker worker;
    CtBool flagTask = CT_FALSE;
    ASSERT_EQ(worker.isRunning(), CT_FALSE);
    worker.setTaskFunc([&flagTask](){flagTask = CT_TRUE; CtThread::sleepFor(TASK_DURATION_MS);});
    worker.runTask();
    ASSERT_EQ(worker.isRunning(), CT_TRUE);
    worker.joinTask();
    ASSERT_EQ(flagTask, CT_TRUE);
}

/**
 * @brief CtWorkerTest02
 * 
 * @details
 * Test if CtWorkerError is thrown when task added while another is still running
 * 
 * @ref FR-005-003-011
 * 
 */
TEST(CtWorker, CtWorkerTest02) {
    CtWorker worker;
    worker.setTaskFunc([](){CtThread::sleepFor(TASK_DURATION_MS);});
    worker.runTask();
    EXPECT_THROW({
        worker.setTaskFunc([](){CtThread::sleepFor(TASK_DURATION_MS);});
    }, CtWorkerError);
    EXPECT_THROW({
        worker.runTask();
    }, CtWorkerError);
}

/**
 * @brief CtWorkerTest03
 * 
 * @details
 * Test the main functionality of CtWorker methods and the worker callback functionality.
 * 
 * @ref FR-005-003-009
 * 
 */
TEST(CtWorker, CtWorkerTest03) {
    CtWorker worker;
    CtBool flagTask = CT_FALSE;
    CtBool flagCallback = CT_FALSE;
    CtBool flagWorkerCallback = CT_FALSE;
    ASSERT_EQ(worker.isRunning(), CT_FALSE);
    CtTask task;
    task.setTaskFunc([&flagTask](){flagTask = CT_TRUE; CtThread::sleepFor(TASK_DURATION_MS);});
    task.setCallbackFunc([&flagCallback](){flagCallback = CT_TRUE;});
    worker.setTask(task, [&flagWorkerCallback](){flagWorkerCallback = CT_TRUE;});
    worker.runTask();
    ASSERT_EQ(worker.isRunning(), CT_TRUE);
    ASSERT_EQ(flagCallback, CT_FALSE);
    worker.joinTask();
    ASSERT_EQ(flagTask, CT_TRUE);
    ASSERT_EQ(flagCallback, CT_TRUE);
    ASSERT_EQ(flagWorkerCallback, CT_TRUE);
}
