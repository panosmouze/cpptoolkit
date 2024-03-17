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
 * @file CtSink.hpp
 * @brief 
 * @date 09-03-2024
 * 
 */

#ifndef INCLUDE_CTSINK_HPP_
#define INCLUDE_CTSINK_HPP_

#include "io/CtBlock.hpp"

class CtSink : public CtBlock, CtThread {
public:
    EXPORTED_API void startSink();
    EXPORTED_API void stopSink();
    EXPORTED_API void joinSink();
    EXPORTED_API void setData(std::vector<CtBlockDataPtr> p_data);

protected:
    EXPORTED_API CtSink();
    EXPORTED_API ~CtSink();
    EXPORTED_API virtual CtUInt32 write(CtBlockDataPtr& p_data) = 0;

private:
    void loop() override;
};

#endif //INCLUDE_CTSINK_HPP_