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
 * @file CtFileSource.hpp
 * @brief 
 * @date 08-03-2024
 * 
 */

#ifndef INCLUDE_CTFILESOURCE_HPP_
#define INCLUDE_CTFILESOURCE_HPP_

#include "io/CtSource.hpp"

#include <fstream>
#include <sstream>
#include <cstring>

class CtFileSource : public CtSource {
public:
    /**
     * @brief Constructs the CtFileSource object.
     * 
     * @param p_fileName Filename.
     */
    EXPORTED_API CtFileSource(const std::string& p_fileName);

    /**
     * @brief Destructor for CtFileSource.
     *
     * Performs any necessary cleanup.
     */
    EXPORTED_API ~CtFileSource();

    /**
     * @brief Set the the delimiter of read() method.
     * 
     * @param p_delim The delimiter.
     * @param p_delim_size The delimiter size.
     */
    EXPORTED_API void setDelimiter(const char* p_delim, CtUInt8 p_delim_size);

protected:
    EXPORTED_API virtual CtBlockDataPtr read(CtUInt32& eventCode) override;

private:
    std::ifstream m_file; ///< File stream.
    char* m_delim; ///< Batch read delimiter.
    CtUInt8 m_delim_size; ///< Delimeter size.
};

#endif //INCLUDE_CTFILESOURCE_HPP_