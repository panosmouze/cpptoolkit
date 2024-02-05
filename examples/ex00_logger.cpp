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
 * @file ex00_logger.cpp
 * @brief 
 * @date 05-02-2024
 * 
 */

#include "CtIO.hpp"

int main() {
    // create logger object with log level set to ERROR and service name TestComp
    CtLogger logger(CtLogger::Level::ERROR, "TestComp");

    // create sink object for terminal log
    CtLogSink log;

    // create sink object for file log
    CtFileSink file("log.txt");

    // add sinks to the logger object
    logger.addSink(&log);
    logger.addSink(&file);

    // log messages
    logger.log_warning("warning 1");
    logger.log_debug("debug 1");
    logger.log_error("error 1");
    logger.log_warning("warning 2");
    logger.log_info("info 1");
    logger.log_info("info 2");
    logger.log_critical("critical 1");
    return 0;
}
