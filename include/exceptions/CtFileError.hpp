/*
 * CtFileError.hpp
 *
 *  Created on: Nov 12, 2023
 *      Author: Mouzenidis Panagiotis
 */

#ifndef INCLUDE_EXCEPTIONS_CTFILEERROR_HPP_
#define INCLUDE_EXCEPTIONS_CTFILEERROR_HPP_

#include "exceptions/CtException.hpp"

class CtFileError : public CtException {
public:
    explicit CtFileError(const std::string& msg): CtException(msg) {};
};

#endif //INCLUDE_EXCEPTIONS_CTFILEERROR_HPP_