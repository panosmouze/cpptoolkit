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
 * @file CtNetworkExceptions.hpp
 * @brief CtNetworkExceptions header file.
 * @date 18-01-2024
 * 
 */

#ifndef INCLUDE_CTNETWORKEXCEPTIONS_HPP_
#define INCLUDE_CTNETWORKEXCEPTIONS_HPP_

#include "core.hpp"

/**
 * @brief This exception is thrown when a socket error occurs.
 * 
 */
class CtSocketError : public CtException {
public:
    explicit CtSocketError(const CtString& msg): CtException(msg) {};
};

/**
 * @brief This exception is thrown when a socket bind error occurs.
 * 
 */
class CtSocketBindError : public CtException {
public:
    explicit CtSocketBindError(const CtString& msg): CtException(msg) {};
};

/**
 * @brief This exception is thrown when a socket listen error occurs.
 * 
 */
class CtSocketPollError : public CtException {
public:
    explicit CtSocketPollError(const CtString& msg): CtException(msg) {};
};

/**
 * @brief This exception is thrown when a socket accept error occurs.
 * 
 */
class CtSocketReadError : public CtException {
public:
    explicit CtSocketReadError(const CtString& msg): CtException(msg) {};
};

/**
 * @brief This exception is thrown when a socket connect error occurs.
 * 
 */
class CtSocketWriteError : public CtException {
public:
    explicit CtSocketWriteError(const CtString& msg): CtException(msg) {};
};

#endif //INCLUDE_CTNETWORKEXCEPTIONS_HPP_
