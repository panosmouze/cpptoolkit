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
 * @file ctservicepool.cpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#include <gtest/gtest.h>
#include "CtThreading.hpp"

void f1(uint32_t* idx) {
    *idx += 1;
}


TEST(CtServicePool, ServicePoolFunctionalityUsingNormalFunction) {
    uint32_t idx[15] = {0};
    // set slot time to 100ms
    CtService::m_slot_time = 100;
    // create a new service and run f1 every 10 slots => 1s
    CtServicePool pool(2);
    for (uint8_t i = 0; i< 15; i++) {
        pool.addTaskFunc(i+1, std::to_string(i), f1, &idx[i]);
    }
    // start services
    pool.startServices();
    // sleep for 3000ms
    CtThread::sleepFor(3000);
    // stop services
    pool.shutdownServices();
    for (uint8_t i = 0; i < 14; i++) {
        ASSERT_GT(idx[i], 0);
    }
};


TEST(CtServicePool, ServicePoolFunctionalityUsingCtTask) {
    uint32_t idx[15] = {0};
    // set slot time to 100ms
    CtService::m_slot_time = 100;
    // create a new service and run f1 every 10 slots => 1s
    CtServicePool pool(2);
    for (uint8_t i = 0; i< 15; i++) {
        pool.addTaskFunc(i+2, std::to_string(i), [&idx, i](){
            idx[i]++;
        });
    }
    // start services
    pool.startServices();
    // sleep for 3000ms
    CtThread::sleepFor(3000);
    // stop services
    pool.shutdownServices();
    for (uint8_t i = 0; i < 14; i++) {
        ASSERT_GT(idx[i], 0);
    }
};
