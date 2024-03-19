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
 * @file CtTextFileSource.hpp
 * @brief 
 * @date 10-03-2024
 * 
 */

#ifndef INCLUDE_CTTEXTFILESOURCE_HPP_
#define INCLUDE_CTTEXTFILESOURCE_HPP_

#include "io/sources/CtFileSource.hpp"

class CtTextFileSource : public CtFileSource {
public:
    /**
     * @brief Constructs the CtFileSource object.
     * 
     * @param p_fileName Filename.
     */
    EXPORTED_API CtTextFileSource(const std::string& p_fileName);

    /**
     * @brief Destructor for CtFileSource.
     *
     * Performs any necessary cleanup.
     */
    EXPORTED_API ~CtTextFileSource();

protected:
    EXPORTED_API virtual CtUInt32 read(CtBlockDataPtr& p_data) override;
    EXPORTED_API virtual CtBlockDataPtr newResource() override;
};

#endif //INCLUDE_CTTEXTFILESOURCE_HPP_