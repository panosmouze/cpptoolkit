/*
 * CtException.hpp
 *
 *  Created on: Nov 12, 2023
 *      Author: Mouzenidis Panagiotis
 */

#ifndef INCLUDE_EXCEPTIONS_CTEXCEPTION_HPP_
#define INCLUDE_EXCEPTIONS_CTEXCEPTION_HPP_

#include <stdexcept>

class CtException : public std::exception {
protected:
    explicit CtException(const std::string& msg) : m_msg(msg) {};

public:
    const char* what() const noexcept override {
        return m_msg.c_str();
    };

private:
    std::string m_msg;
};

#endif /* INCLUDE_EXCEPTIONS_CTEXCEPTION_HPP_ */
