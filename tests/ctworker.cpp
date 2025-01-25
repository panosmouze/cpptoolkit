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

void f1(bool* flag) {
    *flag = true;
}

void callback(bool* flag) {
    *flag = true;
}

TEST(CtWorker, WorkerFunctionalityUsingNormalFunction) {
    bool task_flag = false;
    bool callback_flag = false;
    // create a new service and run f1 every 10 slots => 1s
    CtWorker worker;
    worker.setTaskFunc(f1, &task_flag);
    // run service
    worker.runTask();
    // wait for worker to finish the task
    worker.joinTask();
    ASSERT_EQ(task_flag, true);
    ASSERT_EQ(callback_flag, false);
};


TEST(CtWorker, WorkerFunctionalityUsingCtTask) {
    bool task_flag = false;
    bool callback_flag = false;
    // setup task
    CtTask task;
    task.setTaskFunc(f1, &task_flag);
    task.setCallbackFunc(callback, &callback_flag);
    // create a new worker
    CtWorker worker;
    worker.setTask(task);
    // run task
    worker.runTask();
    // wait for worker to finish the task
    worker.joinTask();
    ASSERT_EQ(task_flag, true);
    ASSERT_EQ(callback_flag, true);
};
