/*
 * definitions.hpp
 *
 *  Created on: Nov 12, 2023
 *      Author: Mouzenidis Panagiotis
 */

#ifndef INCLUDE_DEFINITIONS_HPP_
#define INCLUDE_DEFINITIONS_HPP_

#include "version.hpp"

#ifdef _WIN32
    #define EXPORTED_API __declspec(dllexport)
#else
    #define EXPORTED_API __attribute__((visibility("default")))
#endif

#endif /* INCLUDE_DEFINITIONS_HPP_ */
