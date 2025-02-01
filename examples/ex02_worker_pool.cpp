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
 * @file ex02_worker_pool.cpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#include "cpptoolkit.hpp"

#include <iostream>

/** Helper functions */
void f1(CtAtomic<CtUInt8>* cnt) {
    (*cnt) += 1;
}

void callback(CtAtomic<CtUInt8>* cnt) {
    (*cnt) -= 1;
}

/** Cases functions */

/**
 * @brief This case shows how to initialize a worker pool object with 10 workers.
 *          The loop adds 100 tasks on the worker pool's queue using a lambda 
 *          function. After that we wait for the tasks to be executed.
 * 
 */
void case01() {
    CtWorkerPool pool(10);
    CtAtomic<CtUInt8> cnt = 0;
    for (int i = 0; i < 100; i++) {
        pool.addTask([&cnt](){
            cnt++;
        });
    }
    pool.join();
    std::cout << std::to_string(cnt) << std::endl;
}

/**
 * @brief This case shows how to initialize a worker pool object with 10 workers.
 *          The loop adds 100 tasks on the worker pool's queue using a normal 
 *          function. After that we wait for the tasks to be executed.
 * 
 */
void case02() {
    CtWorkerPool pool(10);
    CtAtomic<CtUInt8> cnt = 0;
    for (int i = 0; i < 100; i++) {
        pool.addTask(f1, &cnt);
    }
    pool.join();
    std::cout << std::to_string(cnt) << std::endl;
}

/**
 * @brief This case shows how to initialize a worker pool object with 10 workers.
 *          The loop adds 100 tasks on the worker pool's queue using a CtTask obj. 
 *          After that we wait for the tasks to be executed.
 * 
 */
void case03() {
    CtWorkerPool pool(10);
    CtTask task;
    CtAtomic<CtUInt8> cnt = 0;
    for (int i = 0; i < 100; i++) {
        task.setTaskFunc(f1, &cnt);
        task.setCallbackFunc(callback, &cnt);
        pool.addTask(task);
    }
    pool.join();
    std::cout << std::to_string(cnt) << std::endl;
}

/** Run all cases */
int main() {
    case01();
    case02();
    case03();
    return 0;
}
