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
 * @file ctservice.cpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#include <gtest/gtest.h>
#include "cpptoolkit.hpp"

void f1(uint32_t* idx) {
    *idx += 1;
}


TEST(CtService, ServiceFunctionalityUsingNormalFunction) {
    uint32_t idx = 0;
    // set slot time to 100ms
    CtService::m_slot_time = 100;
    // create a new service and run f1 every 10 slots => 1s
    CtService service(10, f1, &idx);
    // run service
    service.runService();
    // sleep for 1500ms
    CtThread::sleepFor(1500);
    // stop service
    service.stopService();
    ASSERT_EQ(idx, 2);
};


TEST(CtService, ServiceFunctionalityUsingCtTask) {
    uint32_t idx = 0;
    // set slot time to 100ms
    CtService::m_slot_time = 100;
    CtTask task;
    task.setTaskFunc([&idx](){idx++;});
    // create a new service and run task every 10 slots => 1s
    CtService service(10, task);
    // run service
    service.runService();
    // sleep for 1500ms
    CtThread::sleepFor(1500);
    // stop service
    service.stopService();
    ASSERT_EQ(idx, 2);
};
