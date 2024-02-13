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
 * @date 31-01-2024
 * 
 */

#ifndef INCLUDE_CTFILESOURCE_HPP_
#define INCLUDE_CTFILESOURCE_HPP_

#include "definitions.hpp"
#include "io/sources/CtSource.hpp"

#include "exceptions/CtFileExceptions.hpp"

#include <fstream>
#include <sstream>
#include <cstring>

/**
 * @brief Represents a simple file reading resource.
 *
 * This class extends CtSource and provides a basic implementation for reading files.
 */
class CtFileSource : public CtSource {
public:
    /**
     * @brief Reads a file reasource.
     *
     * @param msg The value returned from reading the resource.
     * @return bool false if EOF or error.
     */
    EXPORTED_API bool read(CtData* data) override;

protected:
    /**
     * @brief Constructs the CtFileSource object.
     * 
     * @param p_fileName Filename.
     * @param p_delim Source file delimiter.
     * @param p_delim_size Source file delimiter size.
     */
    EXPORTED_API CtFileSource(const std::string& p_fileName, CtBlockType p_type);

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
    EXPORTED_API void setDelimiter(const char* p_delim, uint8_t p_delim_size);

private:
    std::ifstream m_file; ///< File stream.
    char* m_delim; ///< Batch read delimiter.
    uint8_t m_delim_size; ///< Delimeter size.
};

#endif //INCLUDE_CTFILESOURCE_HPP_