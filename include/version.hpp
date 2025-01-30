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
 * @file version.hpp
 * @brief Version information for the project.
 * @date 18-01-2024
 * 
 */

#ifndef INCLUDE_VERSION_HPP_
#define INCLUDE_VERSION_HPP_

/**
 * @brief Version information for the project.
 * 
 * @details
 * The version information is defined by three macros:
 * - CPPTOOLKIT_VERSION_MAJOR
 * - CPPTOOLKIT_VERSION_MINOR
 * - CPPTOOLKIT_VERSION_PATCH
 * These macros has to be modified after a new release.
 * 
 */
#define CPPTOOLKIT_VERSION_MAJOR 0
#define CPPTOOLKIT_VERSION_MINOR 1
#define CPPTOOLKIT_VERSION_PATCH 0

#define CPPTOOLKIT_VERSION       (CPPTOOLKIT_VERSION_MAJOR ## "." ## CPPTOOLKIT_VERSION_MINOR ## "." ## CPPTOOLKIT_VERSION_PATCH)

#endif //INCLUDE_VERSION_HPP_
