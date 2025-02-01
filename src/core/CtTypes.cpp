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
 * @file CtTypes.cpp
 * @brief 
 * @date 01-02-2025
 * 
 */

#include "core/CtTypes.hpp"

#include "core/exceptions/CtTypeExceptions.hpp"

#include <cstring>
#include <memory>

CtRawData::CtRawData(CtUInt32 p_size) : m_maxSize(p_size) {
    m_data = new CtUInt8[m_maxSize];
    m_size = 0;
};

CtRawData::CtRawData(CtRawData& p_data) : m_maxSize(p_data.maxSize()) {
    m_data = new CtUInt8[m_maxSize];
    clone(p_data);
};

CtRawData::~CtRawData() {
    delete[] m_data;
}

void CtRawData::nextByte(char byte) {
    if (m_size < m_maxSize) {
        m_data[m_size++] = byte;
    }
}

CtUInt8* CtRawData::getNLastBytes(CtUInt32 p_num) {
    if (p_num > m_size) {
        throw CtOutOfRangeError("Data size is out of range.");
    }
    return &m_data[m_size - p_num];
}

void CtRawData::removeNLastBytes(CtUInt32 p_num) {
    if (p_num > m_size) {
        throw CtOutOfRangeError("Data size is out of range.");
    }
    m_size -= p_num;
}

CtUInt32 CtRawData::size() {
    return m_size;
}

CtUInt32 CtRawData::maxSize() {
    return m_maxSize;
}

CtUInt8* CtRawData::get() {
    return m_data;
}

void CtRawData::clone(const CtUInt8* p_data, CtUInt32 p_size) {
    if (p_size > m_maxSize) {
        throw CtOutOfRangeError("Data size is out of range.");
    }
    m_size = p_size;
    memcpy(m_data, p_data, p_size);
}

void CtRawData::clone(CtRawData& p_data) {
    if (p_data.size() > m_maxSize) {
        throw CtOutOfRangeError("Data size is out of range.");
    }
    m_size = p_data.size();
    memcpy(m_data, p_data.get(), p_data.size());
}

void CtRawData::reset() {
    m_size = 0;
}

CtRawData& CtRawData::operator=(CtRawData& other) {
    if (this != &other) {
        clone(other);
    }
    return *this;
}
