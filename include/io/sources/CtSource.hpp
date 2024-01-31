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
 * @file CtSource.hpp
 * @brief 
 * @date 31-01-2024
 * 
 */

#ifndef INCLUDE_CTSOURCE_HPP_
#define INCLUDE_CTSOURCE_HPP_

#include "definitions.hpp"
#include <mutex>

/**
 * @brief Abstract base class representing a source for reading resources.
 *
 * This class provides an interface for sources and includes basic synchronization mechanisms.
 */
class CtSource {
public:
    /**
     * @brief Reads a reasource.
     *
     * @param msg The value returned from reading the resource.
     * @return bool false if EOF or error.
     */
    EXPORTED_API virtual bool read(std::string& msg) = 0;

protected:
    /**
     * @brief Constructor for CtSource.
     *
     * Initializes the CtSource object.
     */
    EXPORTED_API CtSource();

    /**
     * @brief Virtual destructor for CtSource.
     *
     * Ensures proper cleanup in derived classes.
     */
    EXPORTED_API virtual ~CtSource();

    /**
     * @brief Locks the internal mutex for thread-safe operations.
     */
    void lock();

    /**
     * @brief Unlocks the internal mutex.
     */
    void unlock();

private:
    std::mutex m_mtx_control; ///< Internal mutex for synchronization.
};

#endif //INCLUDE_CTSOURCE_HPP_