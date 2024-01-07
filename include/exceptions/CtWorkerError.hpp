/*
 * CtWorkerError.hpp
 *
 *  Created on: Nov 12, 2023
 *      Author: Mouzenidis Panagiotis
 */

#ifndef INCLUDE_EXCEPTIONS_CTWORKERERROR_HPP_
#define INCLUDE_EXCEPTIONS_CTWORKERERROR_HPP_

#include "exceptions/CtException.hpp"

class CtWorkerError : public CtException {
public:
    explicit CtWorkerError(const std::string& msg): CtException(msg) {};
};

#endif //INCLUDE_EXCEPTIONS_CTWORKERERROR_HPP_