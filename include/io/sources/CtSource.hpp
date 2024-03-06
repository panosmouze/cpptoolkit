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
#include "io/CtBlock.hpp"
#include "io/CtIOTypes.hpp"

#include <mutex>
#include <queue>

/**
 * @brief Abstract base class representing a source for reading resources.
 *
 * This class provides an interface for sources and includes basic synchronization mechanisms.
 */
class CtSource : public CtBlock {
public:
    enum class CtSourceEvent : uint8_t {
        Avail,
        Eof
    };

    EXPORTED_API virtual CtData* get();
    EXPORTED_API virtual void set(CtData* data);
    EXPORTED_API bool acceptOutType(CtDataType p_type);
    EXPORTED_API void start();
    EXPORTED_API void stop();
    EXPORTED_API void join();

protected:
    /**
     * @brief Reads a reasource.
     *
     * @param msg The value returned from reading the resource.
     * @return bool false if EOF.
     */
    EXPORTED_API virtual bool read(CtData* p_data) = 0;

    EXPORTED_API void setOutType(CtDataType p_type);
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

private:
    std::mutex m_mtx_control; ///< Internal mutex for synchronization.
    std::queue<CtData*> m_queue;
    CtDataType m_outType;
};

#endif //INCLUDE_CTSOURCE_HPP_