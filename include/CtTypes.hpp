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
 * @file CtTypes.hpp
 * @brief 
 * @date 21-01-2024
 * 
 */

#ifndef INCLUDE_CTTYPES_HPP_
#define INCLUDE_CTTYPES_HPP_

#include <stdint.h>
#include <string>

#define CtUInt8 uint8_t
#define CtUInt16 uint16_t
#define CtUInt32 uint32_t
#define CtUInt64 uint64_t

#define CtInt8 int8_t
#define CtInt16 int16_t
#define CtInt32 int32_t
#define CtInt64 int64_t

#define CtString std::string

#define CTNET_BUFFER_SIZE 2048

/**
 * @brief Struct describing a network address.
 * 
 */
typedef struct _CtNetAddress {
    CtString addr;
    CtUInt16 port;
} CtNetAddress;

/**
 * @brief Struct describing data sent over network.
 * 
 */
typedef struct _CtNetMessage {
    CtUInt8 data[CTNET_BUFFER_SIZE];
    CtUInt32 size = CTNET_BUFFER_SIZE;
} CtNetMessage;

#endif //INCLUDE_CTTYPES_HPP_
