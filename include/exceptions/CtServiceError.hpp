/*
 * CtServiceError.hpp
 *
 *  Created on: Nov 12, 2023
 *      Author: Mouzenidis Panagiotis
 */

#ifndef INCLUDE_EXCEPTIONS_CTSERVICEERROR_HPP_
#define INCLUDE_EXCEPTIONS_CTSERVICEERROR_HPP_

#include "CtException.hpp"

class CtServiceError : public CtException {
public:
    explicit CtServiceError(const std::string& msg): CtException(msg) {};
};

#endif /* INCLUDE_EXCEPTIONS_CTSERVICEERROR_HPP_ */
