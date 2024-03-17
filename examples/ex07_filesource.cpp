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
 * @file ex07_filesource.cpp
 * @brief 
 * @date 08-03-2024
 * 
 */

#include "io/sources/CtFileSource.hpp"

#include <iostream>
#include <string>

int main() {
    CtFileSource source("config.ini");
    source.setDelimiter("\n", 1);
    source.connectEvent(CTEVENT_DATA_READY, [&source]{
        std::vector<CtBlockDataPtr> data = source.getData();
        CtRawData* temp = (CtRawData*)data.at(0).get();
        std::cout << std::string((char*)temp->get(), temp->size()) << std::endl;
    });
    source.startSource();
    source.joinSource();
}
