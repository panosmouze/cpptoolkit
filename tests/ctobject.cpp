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
 * @file ctobject.cpp
 * @brief 
 * @date 06-02-2025
 * 
 */

#include <gtest/gtest.h>
#include "cpptoolkit.hpp"

/**************************** Helper definitions ****************************/
#define SLEEP_TIME  100

#define EVENT01     1
#define EVENT02     2
#define EVENT03     3
#define EVENT04     4

class CtObjectTest01 : public CtObject {
public:
    CtObjectTest01() : CtObject() {
        registerEvent(EVENT01);
        registerEvent(EVENT02);
        registerEvent(EVENT03);
    }

    ~CtObjectTest01() {}

    void run() {
        switch(status) {
            case EVENT01:
                triggerEvent(EVENT01);
                status = EVENT02;
                break;
            case EVENT02:
                triggerEvent(EVENT02);
                status = EVENT03;
                break;
            case EVENT03:
                triggerEvent(EVENT03);
                status = EVENT01;
                break;
            default:
                break;
        }
    }

    CtUInt8 status = EVENT01;
};

class CtObjectTest02 : public CtObject {
public:
    CtObjectTest02() : CtObject() {
    }

    ~CtObjectTest02() {}

    void run() {
        EXPECT_THROW({
            triggerEvent(EVENT04);
        }, CtEventNotExistsError);
    }
};

class CtObjectTest03 : public CtObject {
public:
    CtObjectTest03() : CtObject() {
        registerEvent(EVENT01);
        EXPECT_THROW({
            registerEvent(EVENT01);
        }, CtEventAlreadyExistsError);
    }

    ~CtObjectTest03() {}
};

/********************************* Main test ********************************/

/**
 * @brief CtObjectTest01
 * 
 * @details
 * Test main functionality of CtObject methods connectEvent, waitPendingEvents, registerEvent, triggerEvent.
 * 
 */
TEST(CtObject, CtObjectTest01) {
    CtObjectTest01 obj;
    CtUInt8 ctr[3] = {0};
    obj.connectEvent(EVENT01, [&ctr](){
        ctr[0]++;
        CtThread::sleepFor(SLEEP_TIME);
    });
    obj.connectEvent(EVENT02, [&ctr](){
        ctr[1]++;
        CtThread::sleepFor(SLEEP_TIME);
    });
    obj.connectEvent(EVENT03, [&ctr](){
        ctr[2]++;
        CtThread::sleepFor(SLEEP_TIME);
    });

    for (CtUInt8 i = 0; i < 10; i++) {
        obj.run();
    }

    CtTimer timer;
    timer.tic();
    obj.waitPendingEvents();
    CtUInt64 elapsed_time = timer.toc();
    ASSERT_GE(elapsed_time, SLEEP_TIME*10);
    ASSERT_LE(elapsed_time, SLEEP_TIME*12);

    ASSERT_EQ(ctr[0], 4);
    ASSERT_EQ(ctr[1], 3);
    ASSERT_EQ(ctr[2], 3);
}

/**
 * @brief CtObjectTest02
 * 
 * @details
 * Test if CtEventNotExistsError is thrown while calling connectEvent, registerEvent with a not registered event.
 * 
 */
TEST(CtObject, CtObjectTest02) {
    CtObjectTest02 obj;
    obj.run();
    EXPECT_THROW({
        obj.connectEvent(EVENT01, [](){});
    }, CtEventNotExistsError);
}

/**
 * @brief CtObjectTest03
 * 
 * @details
 * Test if CtEventAlreadyExistsError is thrown while calling registerEvent twice with the same event.
 * 
 */
TEST(CtObject, CtObjectTest03) {
    CtObjectTest03 obj;
}
