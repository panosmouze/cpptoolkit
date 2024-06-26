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
 * @date 10-03-2024
 * 
 */

#include "io/sources/CtTextFileSource.hpp"

CtTextFileSource::CtTextFileSource(const std::string& p_fileName) : CtFileSource(p_fileName) {
    CtFileSource::setDelimiter("\n", 1);
    CtBlock::setOutVectorTypes({CtBlockDataType::CtTextData});
}

CtTextFileSource::~CtTextFileSource() {

}

CtBlockDataPtr CtTextFileSource::newResource() {
    CtBlockDataPtr s_textDataPtr(new CtTextData());
    return s_textDataPtr;
}

CtUInt32 CtTextFileSource::read(CtBlockDataPtr& p_data) {
    CtBlockDataPtr s_rawDataPtr = CtFileSource::newResource();
    CtUInt8 eventCode = CtFileSource::read(s_rawDataPtr);

    if (eventCode == CTEVENT_DATA_READY) {
        CtRawData* s_rawData = (CtRawData*)s_rawDataPtr.get();

        CtTextData* s_textData = (CtTextData*)p_data.get();
        s_textData->set(std::string((char*)s_rawData->get(), s_rawData->size()));
    }

    return eventCode;
}
