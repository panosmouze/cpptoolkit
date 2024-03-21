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
 * @file CtSink.cpp
 * @brief 
 * @date 09-03-2024
 * 
 */

#include "io/CtSink.hpp"

#include "exceptions/CtTypeExceptions.hpp"

CtSink::CtSink() {
}

CtSink::~CtSink() {
    stopSink();
}

void CtSink::startSink() {
    CtThread::start();
}

void CtSink::stopSink() {
    CtThread::stop();
    CtBlock::waitPendingEvents();
}

void CtSink::joinSink() {
    CtThread::join();
    CtBlock::waitPendingEvents();
}

void CtSink::loop() {
    if (CtBlock::hasOutData()) {
        std::vector<CtBlockDataPtr> data = CtBlock::getOutData();
        CtUInt32 eventCode = write(data.at(0));
        if (eventCode != CTEVENT_DATA_OUT) {
            triggerEvent(eventCode);
        }
    } else {
        setRunning(false);
    }
}

void CtSink::setData(std::vector<CtBlockDataPtr> p_data) {
    std::vector<CtBlockDataType> types = CtBlock::getInVectorTypes();
    if (types.size() != p_data.size()) {
        throw CtDataTypeInvalid("Invalid input vector size given to sink.");
    }
    for (CtUInt8 idx = 0; idx < p_data.size(); idx++) {
        if (p_data.at(idx).get()->type() != types.at(idx)) {
            throw CtDataTypeInvalid("Invalid data type given to sink." + std::to_string((uint8_t)p_data.at(idx).get()->type()) + "   " + std::to_string((uint8_t)types.at(idx)));
        }
    }
    CtBlock::setOutData(p_data);
    try {
        startSink();
    } catch (...) {
    }
}
