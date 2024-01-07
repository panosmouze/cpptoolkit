/*
 * CtKeyNotFoundError.hpp
 *
 *  Created on: Nov 12, 2023
 *      Author: Mouzenidis Panagiotis
 */

#ifndef INCLUDE_EXCEPTIONS_CTKEYNOTFOUNDERROR_HPP_
#define INCLUDE_EXCEPTIONS_CTKEYNOTFOUNDERROR_HPP_

#include "exceptions/CtException.hpp"

class CtKeyNotFoundError : public CtException {
public:
    explicit CtKeyNotFoundError(const std::string& msg): CtException(msg) {};
};

#endif //INCLUDE_EXCEPTIONS_CTKEYNOTFOUNDERROR_HPP_