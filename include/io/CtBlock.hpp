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
 * @file CtBlock.hpp
 * @brief 
 * @date 06-03-2024
 * 
 */

#ifndef INCLUDE_CTBLOCK_HPP_
#define INCLUDE_CTBLOCK_HPP_

#include "definitions.hpp"

#include "io/CtBlockType.hpp"
#include "io/CtBlockData.hpp"

#include "utils/CtObject.hpp"

#include <vector>
#include <queue>

class CtBlock : public CtObject {
public:
    EXPORTED_API CtUInt32 getInVectorSize();
    EXPORTED_API std::vector<CtBlockDataType> getInVectorTypes();

    EXPORTED_API CtUInt32 getOutVectorSize();
    EXPORTED_API std::vector<CtBlockDataType> getOutVectorTypes();

    EXPORTED_API virtual void process();

protected:
    EXPORTED_API CtBlock();
    EXPORTED_API ~CtBlock();

    EXPORTED_API void setInVectorTypes(std::vector<CtBlockDataType> p_inTypes);
    EXPORTED_API bool hasInData();
    EXPORTED_API void setInData(std::vector<CtBlockDataPtr> p_data);
    EXPORTED_API std::vector<CtBlockDataPtr> getInData();

    EXPORTED_API void setOutVectorTypes(std::vector<CtBlockDataType> p_outTypes);
    EXPORTED_API bool hasOutData();
    EXPORTED_API void setOutData(std::vector<CtBlockDataPtr> p_data);
    EXPORTED_API std::vector<CtBlockDataPtr> getOutData();

private:
    std::mutex m_mtx_out; ///< Mutex for controlling access to output resources.
    std::mutex m_mtx_in; ///< Mutex for controlling access to input resources.
    std::vector<CtBlockDataType> m_inTypes;
    std::vector<CtBlockDataType> m_outTypes;
    std::queue<std::vector<CtBlockDataPtr>> m_inData;
    std::queue<std::vector<CtBlockDataPtr>> m_outData;
};

#endif //INCLUDE_CTBLOCK_HPP_