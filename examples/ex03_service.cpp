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
 * @file ex03_service.cpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#include "CtThreading.hpp"
#include "CtUtils.hpp"
#include "CtIO.hpp"

CtLogger logger(CtLogger::Level::DEBUG, "SERVICE_EX03");

/** Cases functions */

/**
 * @brief This case shows how to initialize a worker object using a lambda function.
 * 
 */
void case01() {
    uint8_t cnt = 0;
    CtService service(10, [&cnt](){cnt++;});
    service.runService();

    CtThread::sleepFor(1900);
    service.stopService();
    logger.log_info(std::to_string(cnt));
}

/** Run all cases */
int main() {
    CtLogSink logSink;
    logger.addSink(&logSink);
    case01();
    return 0;
}
