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

#include "exceptions/CtFileExceptions.hpp"

CtFileInput::CtFileInput(const std::string& p_fileName) {
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

void CtFileInput::setDelimiter(const char* p_delim, CtUInt8 p_delim_size) {
    if (p_delim_size > 0 && p_delim != nullptr) {
        m_delim_size = p_delim_size;
        m_delim = new char[m_delim_size];
        memcpy(m_delim, p_delim, m_delim_size);
    }
}

bool CtFileInput::read(CtRawData* p_data) {
    bool s_res = false;

    if (m_file.is_open()) {
        char next_char;
        CtUInt8* delim_ptr = nullptr;

        while (m_file.get(next_char)) {
            p_data->nextByte(next_char);
            
            if (m_delim != nullptr && p_data->size() >= m_delim_size) {
                delim_ptr = p_data->getNLastBytes(m_delim_size);

                if (memcmp(delim_ptr, m_delim, m_delim_size) == 0) {
                    p_data->removeNLastBytes(m_delim_size);
                    break;
                }
            }

            if (p_data->size() == p_data->maxSize()) {
                break;
            }
        }

        if (p_data->size() > 0) {
            s_res = true;
        } else if (m_file.eof()) {
            s_res = false;
        }
    } else {
        throw CtFileReadError("File is not open.");
    }

    return s_res;
}
