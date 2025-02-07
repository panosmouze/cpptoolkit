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
 * @file CtFileInput.cpp
 * @brief 
 * @date 08-03-2024
 * 
 */

#include "io/CtFileInput.hpp"

CtFileInput::CtFileInput(const CtString& p_fileName) {
    m_delim = nullptr;
    m_delim_size = 0;
    m_file.open(p_fileName, std::ofstream::in);
    if (!m_file.is_open()) {
        throw CtFileReadError("File cannot open.");
    }
}

CtFileInput::~CtFileInput() {
    if (m_file.is_open()) {
        m_file.close();
    }
    if (m_delim != nullptr) {
        delete[] m_delim;
    }
}

void CtFileInput::setDelimiter(const CtChar* p_delim, CtUInt8 p_delim_size) {
    if (p_delim_size > 0 && p_delim != nullptr) {
        m_delim_size = p_delim_size;
        m_delim = new CtChar[m_delim_size];
        memcpy(m_delim, p_delim, m_delim_size);
    } else {
        m_delim_size = 0;
        if (m_delim != nullptr) {
            delete[] m_delim;
        }
    }
}

CtBool CtFileInput::read(CtRawData* p_data) {
    CtBool s_res = CT_FALSE;

    if (m_file.is_open()) {
        CtChar next_char;
        CtUInt8* delim_ptr = nullptr;
        p_data->reset();

        while (m_file.get(next_char)) {
            try {
                p_data->setNextByte(next_char);
            } catch (const CtOutOfRangeError& e) {
                m_file.seekg(-(m_delim_size+1), std::ios::cur);
                p_data->removeNLastBytes(m_delim_size);
                break;
            }
            
            if (m_delim != nullptr && p_data->size() >= m_delim_size) {
                delim_ptr = p_data->getNLastBytes(m_delim_size);

                if (memcmp(delim_ptr, m_delim, m_delim_size) == 0) {
                    p_data->removeNLastBytes(m_delim_size);
                    break;
                }
            }
        }

        if (p_data->size() > 0) {
            s_res = CT_TRUE;
        } else if (m_file.eof()) {
            s_res = CT_FALSE;
        }
    } else {
        throw CtFileReadError("File is not open.");
    }

    return s_res;
}
