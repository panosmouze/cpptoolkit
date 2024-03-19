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
 * @date 08-03-2024
 * 
 */

#include "io/sources/CtFileSource.hpp"

#include "exceptions/CtFileExceptions.hpp"

CtFileSource::CtFileSource(const std::string& p_fileName) {
    CtBlock::setOutVectorTypes({CtBlockDataType::CtRawData});
    m_delim = nullptr;
    m_delim_size = 0;
    m_file.open(p_fileName, std::ofstream::in);
    if (!m_file.is_open()) {
        throw CtFileReadError("File cannot open.");
    }
}

CtFileSource::~CtFileSource() {
    stopSource();
    if (m_file.is_open()) {
        m_file.close();
    }
    if (m_delim != nullptr) {
        delete[] m_delim;
    }
}

void CtFileSource::setDelimiter(const char* p_delim, CtUInt8 p_delim_size) {
    if (p_delim_size > 0 && p_delim != nullptr) {
        m_delim_size = p_delim_size;
        m_delim = new char[m_delim_size];
        memcpy(m_delim, p_delim, m_delim_size);
    }
}

CtBlockDataPtr CtFileSource::newResource() {
    CtBlockDataPtr s_rawDataPtr(new CtRawData(1024));
    return s_rawDataPtr;
}

CtUInt32 CtFileSource::read(CtBlockDataPtr& p_data) {
    CtUInt8 eventCode = CTEVENT_NO_EVENT;

    if (m_file.is_open()) {
        if (m_file.eof()) {
            eventCode = CTEVENT_EOF;
        } else {
            CtRawData* s_data = (CtRawData*)p_data.get();
            char next_char;
            CtUInt8* delim_ptr = nullptr;

            while (m_file.get(next_char)) {
                s_data->nextByte(next_char);
                
                if (m_delim != nullptr && s_data->size() >= m_delim_size) {
                    delim_ptr = s_data->getNLastBytes(m_delim_size);

                    if (memcmp(delim_ptr, m_delim, m_delim_size) == 0) {
                        s_data->removeNLastBytes(m_delim_size);
                        break;
                    }
                }

                if (s_data->size() == s_data->maxSize()) {
                    break;
                }
            }

            if (s_data->size() > 0) {
                eventCode = CTEVENT_DATA_READY;
            }
        }
    } else {
        eventCode = CTEVENT_DATA_READ_FAIL;
    }

    return eventCode;
}
