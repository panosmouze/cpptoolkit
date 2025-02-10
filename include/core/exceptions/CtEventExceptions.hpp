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
 * @file CtEventExceptions.hpp
 * @brief CtEventExceptions header file.
 * @date 02-02-2024
 * 
 */

#ifndef INCLUDE_CTEVENTEXCEPTIONS_HPP_
#define INCLUDE_CTEVENTEXCEPTIONS_HPP_

#include "core.hpp"

/**
 * @brief This exception is thrown when an event does not exist in the event manager.
 * 
 * @ref FR-001-001-019
 * @ref FR-001-001-002
 * @ref FR-001-001-003
 */
class CtEventNotExistsError : public CtException {
public:
    explicit CtEventNotExistsError(const CtString& msg): CtException(msg) {};
};

/**
 * @brief This exception is thrown when an event already exists in the event manager.
 * 
 * @ref FR-001-001-018
 * @ref FR-001-001-002
 * @ref FR-001-001-003
 */
class CtEventAlreadyExistsError : public CtException {
public:
    explicit CtEventAlreadyExistsError(const CtString& msg): CtException(msg) {};
};

#endif //INCLUDE_CTEVENTEXCEPTIONS_HPP_