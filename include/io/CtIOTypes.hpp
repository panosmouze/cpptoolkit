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
 * @file CtIOTypes.hpp
 * @brief 
 * @date 08-02-2024
 * 
 */

#ifndef INCLUDE_CTIOTYPES_HPP_
#define INCLUDE_CTIOTYPES_HPP_

#include "definitions.hpp"

/**
 * @brief Abstract struct used as base struct for data IO in sources and sinks.
 * 
 */
struct CtData {
};

/**
 * @brief Struct used for data in file IO operations.
 * 
 */
struct CtFileData : CtData {
    char* data; ///< Data buffer.
    const uint32_t size; ///< Total number of characters the buffer can hold.
    uint32_t rsize; ///< Real number of characters the buffer holds.

    EXPORTED_API CtFileData(uint32_t p_size);
    EXPORTED_API ~CtFileData();
};

#endif //INCLUDE_CTIOTYPES_HPP_