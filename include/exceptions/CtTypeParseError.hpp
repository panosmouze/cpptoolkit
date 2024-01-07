/*
 * CtTypeParseError.hpp
 *
 *  Created on: Nov 12, 2023
 *      Author: Mouzenidis Panagiotis
 */

#ifndef INCLUDE_EXCEPTIONS_CTTYPEPARSEERROR_HPP_
#define INCLUDE_EXCEPTIONS_CTTYPEPARSEERROR_HPP_

#include "exceptions/CtException.hpp"

class CtTypeParseError : public CtException {
public:
    explicit CtTypeParseError(const std::string& msg): CtException(msg) {};
};

#endif //INCLUDE_EXCEPTIONS_CTTYPEPARSEERROR_HPP_