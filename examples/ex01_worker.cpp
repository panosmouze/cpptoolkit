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
 * @file ex01_worker.cpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#include "cpptoolkit.hpp"

#include <iostream>

/** Helper functions */
void f1() {
    std::cout << "Task start f1" << std::endl;
    CtThread::sleepFor(1000);
    std::cout << "Task stop f1" << std::endl;
}

void callback() {
    std::cout << "Callback called" << std::endl;
}

/** Cases functions */

/**
 * @brief This case shows how to initialize a worker object using a lambda function.
 * 
 */
void case01() {
    CtWorker worker;
    worker.setTaskFunc([](){
        std::cout << "Task start lambda 1" << std::endl;
        CtThread::sleepFor(1000);
        std::cout << "Task stop lambda 1" << std::endl;
    });
    worker.runTask();
    worker.joinTask();
}

/**
 * @brief This case shows how to initialize a worker object using a normal function.
 * 
 */
void case02() {
    CtWorker worker;
    worker.setTaskFunc(f1);
    worker.runTask();
    worker.joinTask();
}

/**
 * @brief This case shows how to initialize a worker object using a task object.
 *          In this case a callback function can be set to.
 * 
 */
void case03() {
    CtWorker worker;
    CtTask task;
    task.setTaskFunc(f1);
    task.setCallbackFunc(callback);
    worker.setTask(task);
    worker.runTask();
    worker.joinTask();
}

/** Run all cases */
int main() {
    case01();
    case02();
    case03();
    return 0;
}
