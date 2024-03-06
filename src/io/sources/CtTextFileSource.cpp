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
 * @file CtTextFileSource.cpp
 * @brief 
 * @date 11-02-2024
 * 
 */

#include "io/sources/CtTextFileSource.hpp"

#include "exceptions/CtGenericExeptions.hpp"

CtTextFileSource::CtTextFileSource(const std::string& p_fileName) : CtFileSource(p_fileName) {
    setOutType(CtDataType::CtTextData);
    setBlockType(CtBlockType::CtTextFileSource);
    setDelimiter("\n", 1);
}

CtTextFileSource::~CtTextFileSource() {
    
}

CtData* CtTextFileSource::get() {
    CtBinaryData* s_data = static_cast<CtBinaryData*>(CtFileSource::get());
    CtTextData* res_data = nullptr;
    if (s_data != nullptr) {
        res_data = new CtTextData;
        res_data->line = std::string(s_data->data, s_data->rsize);
        delete s_data;
    }
    return res_data;
}
