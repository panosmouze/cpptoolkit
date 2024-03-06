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
 * @date 11-02-2024
 * 
 */

#ifndef INCLUDE_CTBLOCK_HPP_
#define INCLUDE_CTBLOCK_HPP_

#include "definitions.hpp"

#include "io/CtIOTypes.hpp"
#include "threading/CtThread.hpp"
#include "utils/CtObject.hpp"

class CtBlock : public CtThread, public CtObject {
public:
    enum class CtBlockState : uint8_t {
        IDLE,
        RUNNING
    };

    EXPORTED_API CtBlockType getBlockType();

protected:
    EXPORTED_API CtBlock();
    EXPORTED_API ~CtBlock();

    EXPORTED_API CtBlockState getState();
    EXPORTED_API void setState(CtBlockState p_state);
    EXPORTED_API void setBlockType(CtBlockType p_blockType);

protected:
    CtBlockType m_type;
    std::atomic<CtBlockState> m_state;
};

#endif //INCLUDE_CTBLOCK_HPP_