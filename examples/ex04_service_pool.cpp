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
 * @file ex04_service_pool.cpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#include "cpptoolkit.hpp"

#include <iostream>

/** Helper functions */

void f1(CtUInt8* cnt, int i) {
    cnt[i]++;
}

/** Cases functions */

/**
 * @brief This case shows how to initialize a service pool object. This pool runs 50 services
 *          using 5 workers. Each service runs every 100 slots (1s). In this case the service 
 *          is initialized using a lambda function. After 2s another loop deletes the last 5 
 *          services.
 * 
 */
void case01() {
    CtService::m_slot_time = 10;
    CtServicePool pool(5);
    CtUInt8 cnt[50] = {0};
    for (int i = 0; i < 50; i++) {
        pool.addTaskFunc(100, ToCtString(i), [&cnt, i](){
            cnt[i]++;
        });
    }

    CtThread::sleepFor(2050);
    for (int i = 45; i < 50; i++) {
        pool.removeTask(ToCtString(i));
    }
    CtThread::sleepFor(3050);
    pool.shutdownServices();
    for (int i = 0; i < 50; i++) {
        std::cout << "idx: " + ToCtString(i) + ", cnt: " + ToCtString(cnt[i]) << std::endl;
    }
}

/**
 * @brief This case shows how to initialize a service pool object. This pool runs 50 services
 *          using 5 workers. Each service runs every 100 slots (1s). In this case the service 
 *          is initialized using a normal function. After 2s another loop deletes the last 5 
 *          services.
 * 
 */
void case02() {
    CtService::m_slot_time = 10;
    CtServicePool pool(5);
    CtUInt8 cnt[50] = {0};
    for (int i = 0; i < 50; i++) {
        pool.addTaskFunc(100, ToCtString(i), f1, cnt, i);
    }

    CtThread::sleepFor(2050);
    for (int i = 45; i < 50; i++) {
        pool.removeTask(ToCtString(i));
    }
    CtThread::sleepFor(3050);
    pool.shutdownServices();
    for (int i = 0; i < 50; i++) {
        std::cout << "idx: " + ToCtString(i) + ", cnt: " + ToCtString(cnt[i]) << std::endl;
    }
}

/**
 * @brief This case shows how to initialize a service pool object. This pool runs 50 services
 *          using 5 workers. Each service runs every 100 slots (1s). In this case the service 
 *          is initialized using a CtTask object. After 2s another loop deletes the last 5 
 *          services.
 * 
 */
void case03() {
    CtService::m_slot_time = 10;
    CtServicePool pool(5);
    CtUInt8 cnt[50] = {0};
    CtTask task;
    for (int i = 0; i < 50; i++) {
        task.setTaskFunc(f1, cnt, i);
        pool.addTask(100, ToCtString(i), task);
    }

    CtThread::sleepFor(2050);
    for (int i = 45; i < 50; i++) {
        pool.removeTask(ToCtString(i));
    }
    CtThread::sleepFor(3050);
    pool.shutdownServices();
    for (int i = 0; i < 50; i++) {
        std::cout << "idx: " + ToCtString(i) + ", cnt: " + ToCtString(cnt[i]) << std::endl;
    }
}

/** Run all cases */
int main() {
    case01();
    case02();
    case03();
    return 0;
}
