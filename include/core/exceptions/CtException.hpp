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
 * @file CtException.hpp
 * @brief CtException header file.
 * @date 18-01-2024
 * 
 */

#ifndef INCLUDE_CTEXCEPTION_HPP_
#define INCLUDE_CTEXCEPTION_HPP_

#include "core.hpp"

#include <stdexcept>

/**
 * @brief An exception class for the cpptoolkit library. 
 * 
 * @details
 * This is an abstract class derived from std::exception and is used as a base 
 * class for all the exceptions in the library.
 * 
 */
class CtException : public std::exception {
protected:
    /**
     * @brief Construct a new Ct Exception object
     * 
     * @ref FR-001-001-003
     * 
     * @param msg Message to be stored in the exception.
     */
    explicit CtException(const CtString& msg) : m_msg(msg) {};

public:
    /**
     * @brief This method returns the message stored in the exception.
     * 
     * @ref FR-001-001-001
     * 
     * @return const char* the message stored in the exception.
     */
    const char* what() const noexcept override {
        return m_msg.c_str();
    };

private:
    CtString m_msg;                      /**< The message stored in the exception. */
};

#endif //INCLUDE_CTEXCEPTION_HPP_
