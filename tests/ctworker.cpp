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
 */
TEST(CtWorker, CtWorkerTest01) {
    CtWorker worker;
    bool flagTask = false;
    ASSERT_EQ(worker.isRunning(), false);
    worker.setTaskFunc([&flagTask](){flagTask = true; CtThread::sleepFor(TASK_DURATION_MS);});
    worker.runTask();
    ASSERT_EQ(worker.isRunning(), true);
    worker.joinTask();
    ASSERT_EQ(flagTask, true);
}

/**
 * @brief CtWorkerTest02
 * 
 * @details
 * Test if CtWorkerError is thrown when task added while another is still running
 * 
 */
TEST(CtWorker, CtWorkerTest02) {
    CtWorker worker;
    worker.setTaskFunc([](){CtThread::sleepFor(TASK_DURATION_MS);});
    worker.runTask();
    EXPECT_THROW({
        worker.setTaskFunc([](){CtThread::sleepFor(TASK_DURATION_MS);});
    }, CtWorkerError);
}

/**
 * @brief CtWorkerTest03
 * 
 * @details
 * Test the main functionality of CtWorker methods and the worker callback functionality.
 * 
 */
TEST(CtWorker, CtWorkerTest03) {
    CtWorker worker;
    bool flagTask = false;
    bool flagCallback = false;
    bool flagWorkerCallback = false;
    ASSERT_EQ(worker.isRunning(), false);
    CtTask task;
    task.setTaskFunc([&flagTask](){flagTask = true; CtThread::sleepFor(TASK_DURATION_MS);});
    task.setCallbackFunc([&flagCallback](){flagCallback = true;});
    worker.setTask(task, [&flagWorkerCallback](){flagWorkerCallback = true;});
    worker.runTask();
    ASSERT_EQ(worker.isRunning(), true);
    ASSERT_EQ(flagCallback, false);
    worker.joinTask();
    ASSERT_EQ(flagTask, true);
    ASSERT_EQ(flagCallback, true);
    ASSERT_EQ(flagWorkerCallback, true);
}
