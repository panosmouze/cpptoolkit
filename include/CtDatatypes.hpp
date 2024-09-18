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
 * @file CtBlockData.hpp
 * @brief 
 * @date 07-03-2024
 * 
 */

#ifndef INCLUDE_CTBLOCKDATA_HPP_
#define INCLUDE_CTBLOCKDATA_HPP_

#include "definitions.hpp"

#include <cstring>
#include <memory>

class CtRawData {
public:
    EXPORTED_API CtRawData(CtUInt32 p_size) : m_maxSize(p_size) {
        m_data = new CtUInt8[m_maxSize];
        m_size = 0;
    };

    EXPORTED_API CtRawData(CtRawData& p_data) : m_maxSize(p_data.maxSize()) {
        m_data = new CtUInt8[m_maxSize];
        clone(p_data);
    };

    EXPORTED_API virtual ~CtRawData() {
        delete[] m_data;
    }

    EXPORTED_API void nextByte(char byte) {
        if (m_size < m_maxSize) {
            m_data[m_size++] = byte;
        }
    }

    EXPORTED_API CtUInt8* getNLastBytes(CtUInt32 p_num) {
        return &m_data[m_size - p_num];
    }

    EXPORTED_API void removeNLastBytes(CtUInt32 p_num) {
        m_size -= p_num;
    }

    EXPORTED_API CtUInt32 size() {
        return m_size;
    }

    EXPORTED_API CtUInt32 maxSize() {
        return m_maxSize;
    }

    EXPORTED_API CtUInt8* get() {
        return m_data;
    }

    EXPORTED_API void clone(CtUInt8* p_data, CtUInt32 p_size) {
        if (p_size > m_maxSize) {
            //throw
        }
        m_size = p_size;
        memcpy(m_data, p_data, p_size);
    }

    EXPORTED_API void clone(CtRawData& p_data) {
        if (p_data.size() > m_maxSize) {
            //throw
        }
        m_size = p_data.size();
        memcpy(m_data, p_data.get(), p_data.size());
    }

    EXPORTED_API void reset() {
        m_size = 0;
    }

private:
    CtUInt8* m_data;
    CtUInt32 m_size;
    const CtUInt32 m_maxSize;
};

#endif //INCLUDE_CTBLOCKDATA_HPP_