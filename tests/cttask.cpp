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
 * @file cttask.cpp
 * @brief 
 * @date 03-02-2025
 * 
 */

#include <gtest/gtest.h>
#include "cpptoolkit.hpp"

/**************************** Helper definitions ****************************/

/********************************* Main test ********************************/

/**
 * @brief CtTaskTest01
 * 
 * @details
 * Test the basic functionality of CtTask class.
 * 
 * @ref FR-005-001-001
 * @ref FR-005-001-002
 * @ref FR-005-001-003
 * @ref FR-005-001-004
 * @ref FR-005-001-005
 * @ref FR-005-001-006
 * @ref FR-005-001-007
 * @ref FR-005-001-008
 * 
 */
TEST(CtTask, CtTaskTest01) {
    CtTask task;
    CtUInt8 cnt = 0;
    task.setTaskFunc([&cnt]{cnt++;});
    task.setCallbackFunc([&cnt]{cnt--;});
    std::function<void()> taskFunc = task.getTaskFunc();
    std::function<void()> callbackFunc = task.getCallbackFunc();

    ASSERT_EQ(cnt, 0);
    taskFunc();
    ASSERT_EQ(cnt, 1);
    callbackFunc();
    ASSERT_EQ(cnt, 0);

    CtTask task2 = task;
    taskFunc = task2.getTaskFunc();
    callbackFunc = task2.getCallbackFunc();

    ASSERT_EQ(cnt, 0);
    taskFunc();
    ASSERT_EQ(cnt, 1);
    callbackFunc();
    ASSERT_EQ(cnt, 0);
}
