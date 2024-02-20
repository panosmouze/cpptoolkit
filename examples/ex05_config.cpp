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
 * @file ex05_config.cpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#include "CtIO.hpp"
#include "CtUtils.hpp"

CtLogger logger(CtLogger::Level::DEBUG, "CONFIG_EX05");

/**
 * @brief Write a new configuration file.
 * 
 */
void case01() {
    CtConfigIO config("config.ini");
    try {
        config.read();
    } catch (const CtFileReadError& e) {
        logger.log_error(e.what());
    }
    // write data to config object
    config.writeInt("int_example", -6);
    config.writeDouble("double_example", 43.12421435224);
    config.writeUInt("uint_example", 7);
    config.writeString("email", "panos@testmail.com");
    // write data to the file
    try {
        config.write();
    } catch (const CtFileWriteError& e) {
        logger.log_error(e.what());
    }
}

/**
 * @brief Read a configuration file.
 * 
 */
void case02() {
    CtConfigIO config("config.ini");
    // read data from the file
    try {
        config.read();
    } catch (const CtFileReadError& e) {
        logger.log_error(e.what());
    }
    logger.log_info(std::to_string(config.parseAsInt("int_example")));
    logger.log_info(std::to_string(config.parseAsUInt("uint_example")));
    logger.log_info(std::to_string(config.parseAsDouble("double_example")));
    logger.log_info(config.parseAsString("email"));
}

/**
 * @brief Read and write a configuration file.
 * 
 */
void case03() {
    CtConfigIO config("config.ini");
    // read data from the file
    config.read();
    // add a new key value
    config.writeString("username", "panos");
    // overwrite an existing key value
    config.writeString("email", "panosm@testmail.com");
    // write data to the file
    try {
        config.write();
    } catch (const CtFileWriteError& e) {
        logger.log_error(e.what());
    }
}

/** Run all cases.*/
int main() {
    CtLogSink logSink;
    logger.addSink(&logSink);
    case01();
    case02();
    case03();
    return 0;
}
