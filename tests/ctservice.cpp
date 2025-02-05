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

/**************************** Helper definitions ****************************/
#define SERVICE_INTERVAL_SLOT           10
#define MAIN_SLEEP_MS                   950
#define RESOURCE_CUNSUMING_TASK_MS      200

/********************************* Main test ********************************/

/**
 * @brief CtServiceTest01
 * 
 * @details
 * Test main functionality of CtService methods runService, stopService.
 * 
 */
TEST(CtService, CtServiceTest01) {
    CtUInt8 cnt;
    CtService service(SERVICE_INTERVAL_SLOT, [&cnt](){cnt++;});
    service.runService();
    CtThread::sleepFor(MAIN_SLEEP_MS);
    ASSERT_NE(service.getIntervalValidity(), 1);
    service.stopService();
    ASSERT_GE(cnt, 9);
    ASSERT_LE(cnt, 10);
}

/**
 * @brief CtServiceTest02
 * 
 * @details
 * Test if CtServiceError is thrown if CtService started two times.
 * 
 */
TEST(CtService, CtServiceTest02) {
    CtUInt8 cnt;
    CtService service(SERVICE_INTERVAL_SLOT, [&cnt](){CtThread::sleepFor(RESOURCE_CUNSUMING_TASK_MS); cnt++;});
    service.runService();
    EXPECT_THROW({
        service.runService();
    }, CtServiceError);
}

/**
 * @brief CtServiceTest03
 * 
 * @details
 * Test functionality of getIntervalValidity.
 * 
 */
TEST(CtService, CtServiceTest03) {
    CtUInt8 cnt;
    CtService service(SERVICE_INTERVAL_SLOT, [&cnt](){CtThread::sleepFor(RESOURCE_CUNSUMING_TASK_MS); cnt++;});
    service.runService();
    CtThread::sleepFor(MAIN_SLEEP_MS);
    ASSERT_NE(service.getIntervalValidity(), 1);
}
