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
 * @file CtThreadExceptions.hpp
 * @brief CtThreadExceptions header file.
 * @date 18-01-2024
 * 
 */

#ifndef INCLUDE_CTTHREADEXCEPTIONS_HPP_
#define INCLUDE_CTTHREADEXCEPTIONS_HPP_

#include "core.hpp"

/**
 * @brief This exception is thrown when a thread error occurs.
 * 
 * @ref FR-001-001-007
 * @ref FR-001-001-002
 * @ref FR-001-001-003
 */
class CtThreadError : public CtException {
public:
    explicit CtThreadError(const CtString& msg): CtException(msg) {};
};

/**
 * @brief This exception is thrown when a service pool error occurs.
 * 
 * @ref FR-001-001-008
 * @ref FR-001-001-002
 * @ref FR-001-001-003
 */
class CtServiceError : public CtException {
public:
    explicit CtServiceError(const CtString& msg): CtException(msg) {};
};

/**
 * @brief This exception is thrown when a worker error occurs.
 * 
 * @ref FR-001-001-009
 * @ref FR-001-001-002
 * @ref FR-001-001-003
 */
class CtWorkerError : public CtException {
public:
    explicit CtWorkerError(const CtString& msg): CtException(msg) {};
};

#endif //INCLUDE_CTTHREADEXCEPTIONS_HPP_
