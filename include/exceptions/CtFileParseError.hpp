/*
 * CtFileParseError.hpp
 *
 *  Created on: Nov 12, 2023
 *      Author: Mouzenidis Panagiotis
 */

#ifndef INCLUDE_EXCEPTIONS_CTFILEPARSEERROR_HPP_
#define INCLUDE_EXCEPTIONS_CTFILEPARSEERROR_HPP_

#include "exceptions/CtException.hpp"

class CtFileParseError : public CtException {
public:
    explicit CtFileParseError(const std::string& msg): CtException(msg) {};
};

#endif //INCLUDE_EXCEPTIONS_CTFILEPARSEERROR_HPP_