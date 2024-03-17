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
 * @file CtLogSink.hpp
 * @brief 
 * @date 17-03-2024
 * 
 */

#ifndef INCLUDE_CTLOGSINK_HPP_
#define INCLUDE_CTLOGSINK_HPP_

#include "io/CtSink.hpp"

class CtLogSink : public CtSink {
public:

    /**
     * @brief Constructs the CtLogSink object.
     * 
     */
    EXPORTED_API CtLogSink();

    /**
     * @brief Destructor for CtLogSink.
     *
     * Performs any necessary cleanup.
     */
    EXPORTED_API ~CtLogSink();

protected:
    EXPORTED_API virtual CtUInt32 write(CtBlockDataPtr& p_data) override;
};

#endif //INCLUDE_CTLOGSINK_HPP_