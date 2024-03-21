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
 * @file CtBlock.cpp
 * @brief 
 * @date 06-03-2024
 * 
 */

#include "io/CtBlock.hpp"

CtBlock::CtBlock() {
    registerEvent(CTEVENT_DATA_IN);
    registerEvent(CTEVENT_DATA_OUT);
    registerEvent(CTEVENT_DATA_DROP);
    registerEvent(CTEVENT_DATA_READY);
    registerEvent(CTEVENT_DATA_IN_FAIL);
    registerEvent(CTEVENT_DATA_OUT_FAIL);
    m_inTypes = std::vector<CtBlockDataType>();
    m_outTypes = std::vector<CtBlockDataType>();
}

CtBlock::~CtBlock() {
}

void CtBlock::setInVectorTypes(std::vector<CtBlockDataType> p_inTypes) {
    m_inTypes = p_inTypes;
}

void CtBlock::setOutVectorTypes(std::vector<CtBlockDataType> p_outTypes) {
    m_outTypes = p_outTypes;
}

CtUInt32 CtBlock::getInVectorSize() {
    return m_inTypes.size();
}

CtUInt32 CtBlock::getOutVectorSize() {
    return m_outTypes.size();
}

std::vector<CtBlockDataType> CtBlock::getInVectorTypes() {
    return m_inTypes;
}

std::vector<CtBlockDataType> CtBlock::getOutVectorTypes() {
    return m_outTypes;
}

std::vector<CtBlockDataPtr> CtBlock::getInData() {
    std::unique_lock<std::mutex> lock(m_mtx_in);
    //TODO: throw exception if no in data
    std::vector<CtBlockDataPtr> s_data = m_inData.front();
    m_inData.pop();
    return s_data;
}

void CtBlock::setInData(std::vector<CtBlockDataPtr> p_data) {
    std::unique_lock<std::mutex> lock(m_mtx_in);
    m_inData.push(p_data);
    triggerEvent(CTEVENT_DATA_IN);
}

bool CtBlock::hasInData() {
    std::unique_lock<std::mutex> lock(m_mtx_in);
    return m_inData.size() > 0;
}

std::vector<CtBlockDataPtr> CtBlock::getOutData() {
    std::unique_lock<std::mutex> lock(m_mtx_out);
    //TODO: throw exception if no out data
    std::vector<CtBlockDataPtr> s_data = m_outData.front();
    m_outData.pop();
    triggerEvent(CTEVENT_DATA_OUT);
    return s_data;
}

void CtBlock::setOutData(std::vector<CtBlockDataPtr> p_data) {
    std::unique_lock<std::mutex> lock(m_mtx_out);
    m_outData.push(p_data);
    triggerEvent(CTEVENT_DATA_READY);
}

bool CtBlock::hasOutData() {
    std::unique_lock<std::mutex> lock(m_mtx_out);
    return m_outData.size() > 0;
}

void CtBlock::process() {
    
}