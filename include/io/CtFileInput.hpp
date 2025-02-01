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
 * @file CtFileInput.hpp
 * @brief 
 * @date 08-03-2024
 * 
 */

#ifndef INCLUDE_CTFILEINPUT_HPP_
#define INCLUDE_CTFILEINPUT_HPP_

#include "core.hpp"

#include <fstream>
#include <sstream>
#include <cstring>

/**
 * @brief CtFileInput class for reading data from file.
 * 
 * @details
 * This class provides an interface for reading data from a file. The data can be read in batches or one by one.
 * 
 * @code {.cpp}
 * // create a file input object
 * CtFileInput fileInput("input.txt");
 * CtRawData data;
 * while (fileInput.read(&data)) {
 *    // process data
 * }
 * @endcode
 * 
 */
class CtFileInput {
public:
    /**
     * @brief Constructs the CtFileInput object.
     * 
     * @param p_fileName Filename.
     */
    EXPORTED_API explicit CtFileInput(const CtString& p_fileName);

    /**
     * @brief Destructor for CtFileInput.
     *
     * Performs any necessary cleanup.
     */
    EXPORTED_API ~CtFileInput();

    /**
     * @brief Set the the delimiter of read() method.
     * 
     * @param p_delim The delimiter.
     * @param p_delim_size The delimiter size.
     */
    EXPORTED_API void setDelimiter(const CtChar* p_delim, CtUInt8 p_delim_size);

    /**
     * @brief This method read data from the file.
     * 
     * @param p_data Where to store the data read
     * @return bool Returns True on success or False on EOF.
     */
    EXPORTED_API bool read(CtRawData* p_data);

private:
    std::ifstream m_file;           /**< File stream. */
    CtChar* m_delim;                /**< Batch read delimiter. */
    CtUInt8 m_delim_size;           /**< Delimeter size. */
};

#endif //INCLUDE_CTFILEINPUT_HPP_