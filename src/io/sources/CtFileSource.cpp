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
#include <mutex>
#include <cstring>

CtFileSource::CtFileSource(const std::string& p_fileName, CtBlockType p_type) : CtSource(p_type) {
    m_delim = nullptr;
    m_delim_size = 0;
    m_file.open(p_fileName, std::ofstream::in);
    if (!m_file.is_open()) {
        throw CtFileReadError("File cannot open.");
    }
}

CtFileSource::~CtFileSource() {
    if (m_file.is_open()) {            
        m_file.close();
    }
    if (m_delim != nullptr) {
        delete[] m_delim;
    }
}

void CtFileSource::setDelimiter(const char* p_delim, uint8_t p_delim_size) {
    if (p_delim_size > 0 && p_delim != nullptr) {
        m_delim_size = p_delim_size;
        m_delim = new char[m_delim_size];
        memcpy(m_delim, p_delim, m_delim_size);
    }
}

bool CtFileSource::read(CtData* p_data) {
    bool res = false;
    CtBinaryData* s_data = static_cast<CtBinaryData*>(p_data);

    if (m_file.is_open() && s_data->data != nullptr && s_data->size > 0) {
        char next_char;
        char* delim_ptr = nullptr;
        uint32_t i = 0;
        uint32_t delim_ptr_idx = 0;

        while (m_file.get(next_char)) {
            s_data->data[i++] = next_char;
            
            if (m_delim != nullptr && i >= m_delim_size) {
                delim_ptr_idx = i - m_delim_size;
                delim_ptr = &s_data->data[delim_ptr_idx];

                if (memcmp(delim_ptr, m_delim, m_delim_size) == 0) {
                    i = delim_ptr_idx;
                    break;
                }
            }

            if (i >= s_data->size) {
                break;
            }
        }
        
        s_data->rsize = i;
        res = (i > 0);
    }
    
    return res;
}
