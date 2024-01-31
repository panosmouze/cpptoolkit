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
 * @file CtFileSource.cpp
 * @brief 
 * @date 31-01-2024
 * 
 */

#include "io/sources/CtFileSource.hpp"

CtFileSource::CtFileSource(const std::string& p_fileName) {
    try {
        m_file.open(p_fileName, std::ofstream::in);
    } catch (...) {
        throw CtFileReadError("File cannot open.");
    }
}

CtFileSource::~CtFileSource() {
    if (m_file.is_open()) {            
        m_file.close();
    }
}

bool CtFileSource::read(std::string& msg) {
    bool res;
    lock();
    if(std::getline(m_file, msg)) {
        res = true;
    } else {
        msg = std::string("");
        res = false;
    }
    unlock();
    return res;
}
