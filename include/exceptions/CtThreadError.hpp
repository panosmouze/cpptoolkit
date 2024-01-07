/*
 * CtThreadError.hpp
 *
 *  Created on: Nov 12, 2023
 *      Author: Mouzenidis Panagiotis
 */

#ifndef INCLUDE_EXCEPTIONS_CTTHREADERROR_HPP_
#define INCLUDE_EXCEPTIONS_CTTHREADERROR_HPP_

#include "CtException.hpp"

class CtThreadError : public CtException {
public:
    explicit CtThreadError(const std::string& msg): CtException(msg) {};
};

#endif /* INCLUDE_EXCEPTIONS_CTTHREADERROR_HPP_ */
