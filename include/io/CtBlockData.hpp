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

enum class CtBlockDataType {
    CtBlockData,
    CtRawData,
    CtTextData
};

class CtBlockData;

class CtBlockDataPtr {
public:
    EXPORTED_API CtBlockData* get() {
        return m_ptr.get();
    }

    EXPORTED_API CtBlockDataPtr(CtBlockData* p_data) : m_ptr(p_data) {
    }

    EXPORTED_API ~CtBlockDataPtr() {
    }

private:
    std::shared_ptr<CtBlockData> m_ptr;
};

class CtBlockData {
public:
    EXPORTED_API CtBlockDataType type() {
        return m_dataType;
    }

    EXPORTED_API virtual ~CtBlockData() {

    }

protected:
    EXPORTED_API CtBlockData(CtBlockDataType p_dataType) : m_dataType(p_dataType) {
    }

private:
    const CtBlockDataType m_dataType;
};

class CtRawData : public CtBlockData {
public:
    EXPORTED_API CtRawData(CtUInt32 p_size) : m_maxSize(p_size), CtBlockData(CtBlockDataType::CtRawData) {
        m_data = new CtUInt8[m_maxSize];
        m_size = 0;
    };

    EXPORTED_API CtRawData(CtRawData& p_data) : m_maxSize(p_data.maxSize()), CtBlockData(CtBlockDataType::CtRawData) {
        m_data = new CtUInt8[m_maxSize];
        clone(p_data);
    };

    EXPORTED_API virtual ~CtRawData() override {
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

private:
    CtUInt8* m_data;
    CtUInt32 m_size;
    const CtUInt32 m_maxSize;
};

class CtTextData : public CtBlockData {
public:
    EXPORTED_API CtTextData(CtString& p_text) : CtBlockData(CtBlockDataType::CtTextData) {
        set(p_text);
    };

    EXPORTED_API CtTextData() : CtBlockData(CtBlockDataType::CtTextData) {
    };

    EXPORTED_API ~CtTextData() {
    };

    EXPORTED_API CtString get() {
        return m_text;
    }

    EXPORTED_API void set(CtString s_text) {
        m_text.assign(s_text);
    }

private:
    CtString m_text;
};

#endif //INCLUDE_CTBLOCKDATA_HPP_