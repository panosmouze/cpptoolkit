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
 * @file ex08_filesink.cpp
 * @brief 
 * @date 09-03-2024
 * 
 */

#include "io/sinks/CtFileSink.hpp"

#include <iostream>
#include <string>

int main() {
    CtFileSink sink("config_sink.ini");
    sink.setDelimiter("\n", 1);

    CtRawData* data1 = new CtRawData(1024);
    data1->clone((uint8_t*)"temp text 1", 11);
    CtBlockDataPtr data1ptr(data1);
    sink.setData({data1ptr});

    CtRawData* data2 = new CtRawData(1024);
    data2->clone((uint8_t*)"temp text 2", 11);
    CtBlockDataPtr data2ptr(data2);
    sink.setData({data2ptr});

    sink.joinSink();
}
