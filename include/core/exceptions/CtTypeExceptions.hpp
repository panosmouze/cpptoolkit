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
 * @file CtTypeExceptions.hpp
 * @brief CtTypeExceptions header file.
 * @date 10-03-2024
 * 
 */

#ifndef INCLUDE_CTTYPEEXCEPTIONS_HPP_
#define INCLUDE_CTTYPEEXCEPTIONS_HPP_

#include "core.hpp"

/**
 * @brief This exception is thrown when a type cannot be parsed.
 * 
 * @ref FR-001-001-004
 * @ref FR-001-001-002
 * @ref FR-001-001-003
 */
class CtTypeParseError : public CtException {
public:
    explicit CtTypeParseError(const CtString& msg): CtException(msg) {};
};

/**
 * @brief This exception is thrown when a key is not found in a container.
 * 
 * @ref FR-001-001-005
 * @ref FR-001-001-002
 * @ref FR-001-001-003
 */
class CtKeyNotFoundError : public CtException {
public:
    explicit CtKeyNotFoundError(const CtString& msg): CtException(msg) {};
};

/**
 * @brief This exception is thrown when an index is out of bounds.
 * 
 * @ref FR-001-001-006
 * @ref FR-001-001-002
 * @ref FR-001-001-003
 */
class CtOutOfRangeError : public CtException {
public:
    explicit CtOutOfRangeError(const CtString& msg): CtException(msg) {};
};

#endif //INCLUDE_CTTYPEEXCEPTIONS_HPP_