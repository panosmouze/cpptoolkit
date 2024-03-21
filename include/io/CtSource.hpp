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
 * @date 08-03-2024
 * 
 */

#ifndef INCLUDE_CTSOURCE_HPP_
#define INCLUDE_CTSOURCE_HPP_

#include "io/CtBlock.hpp"

class CtSource : public CtBlock, CtThread {
public:
    EXPORTED_API void startSource();
    EXPORTED_API void stopSource();
    EXPORTED_API void joinSource();
    EXPORTED_API bool hasData();
    EXPORTED_API std::vector<CtBlockDataPtr> getData();
    EXPORTED_API void stopSourceRequest();

protected:
    EXPORTED_API virtual CtBlockDataPtr newResource() = 0;
    EXPORTED_API CtSource();
    EXPORTED_API ~CtSource();
    EXPORTED_API virtual CtUInt32 read(CtBlockDataPtr& p_data) = 0;

private:
    void loop() override;
};

#endif //INCLUDE_CTSOURCE_HPP_