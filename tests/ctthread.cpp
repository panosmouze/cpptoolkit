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
 * @file ctthread.cpp
 * @brief 
 * @date 03-02-2025
 * 
 */

#include <gtest/gtest.h>
#include "cpptoolkit.hpp"

/**************************** Helper definitions ****************************/

#define MAIN_SLEEP_MS       550
#define THREAD_LOOP_MS      100

/**
 * @brief 
 * Helper class used in the CtThreadTest01
 * 
 */
class CtTestThread01 : private CtThread {
public:
    CtTestThread01() : CtThread() {
        cnt = 0;
    }

    ~CtTestThread01() {}

    void start() {
        CtThread::start();
    }

    void stop() {
        CtThread::stop();
    }

    CtUInt8 getCnt() {
        return cnt;
    }

protected:
    void loop() override {
        cnt++;
        CtThread::sleepFor(THREAD_LOOP_MS);
    }

private:
    CtUInt8 cnt;
};

/**
 * @brief 
 * Helper class used in the CtThreadTest02
 * 
 */
class CtTestThread02 : private CtThread {
public:
    CtTestThread02() : CtThread() {
        flag = CT_FALSE;
        CtThread::start();
    }

    ~CtTestThread02() {}

    void join() {
        CtThread::join();
    }

    CtBool isRunning() {
        return CtThread::isRunning();
    }

    CtUInt8 getStatus() {
        return flag;
    }

protected:
    void loop() override {
        CtThread::sleepFor(THREAD_LOOP_MS);
        flag = CT_TRUE;
        setRunning(CT_FALSE);
    }

private:
    CtBool flag;
};

/********************************* Main test ********************************/

/**
 * @brief CtThreadTest01
 * 
 * @details
 * Test the basic functionality of CtThread class start, stop and sleepFor method.
 * 
 * @ref FR-005-002-001
 * @ref FR-005-002-002
 * @ref FR-005-002-003
 * @ref FR-005-002-007
 * @ref FR-005-002-009
 * @ref FR-005-002-010
 * 
 */
TEST(CtThread, CtThreadTest01) {
    CtTestThread01 thread;
    thread.start();
    CtThread::sleepFor(MAIN_SLEEP_MS);
    thread.stop();
    ASSERT_EQ(thread.getCnt(), MAIN_SLEEP_MS/THREAD_LOOP_MS + 1);
}

/**
 * @brief CtThreadTest02
 * 
 * @details
 * Test the basic functionality of CtThread class join method.
 * 
 * @ref FR-005-002-004
 * @ref FR-005-002-005
 * @ref FR-005-002-006
 * @ref FR-005-002-012
 * 
 */
TEST(CtThread, CtThreadTest02) {
    CtTestThread02 thread;
    ASSERT_EQ(thread.isRunning(), CT_TRUE);
    thread.join();
    ASSERT_EQ(thread.getStatus(), CT_TRUE);
}

/**
 * @brief CtThreadTest03
 * 
 * @details
 * Test if CtThreadError is thrown if CtThread started 2 times.
 * 
 * @ref FR-005-002-008
 * 
 */
TEST(CtThread, CtThreadTest03) {
    CtTestThread01 thread;
    thread.start();
    EXPECT_THROW({
        thread.start();
    }, CtThreadError);
}

/**
 * @brief CtThreadTest04
 * 
 * @ref FR-005-002-011
 * 
 */
TEST(CtThread, CtThreadTest04) {
    CtTestThread01 thread;
    thread.start();
}
