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
 * @file CtFileOutput.hpp
 * @brief 
 * @date 09-03-2024
 * 
 */

#ifndef INCLUDE_CTFILEOUTPUT_HPP_
#define INCLUDE_CTFILEOUTPUT_HPP_

#include "core.hpp"

#include <fstream>
#include <sstream>
#include <cstring>
#include <memory>

/**
 * @brief CtFileOutput class for writing data to file.
 * 
 * @details
 * This class provides an interface for writing data to a file. The data can be written in batches or one by one.
 * 
 * @code {.cpp}
 * // create a file output object
 * CtFileOutput fileOutput("output.txt");
 * fileOutput.write("Hello, World!");
 * @endcode
 * 
 */
class CtFileOutput {
public:
    /**
     * @brief Enum representing write mode.
     * 
     * @ref FR-002-002-003
     */
    enum class WriteMode { Append, Truncate };

    /**
     * @brief Constructs the CtFileOutput object.
     * 
     * @ref FR-002-002-001
     * @ref FR-002-002-002
     * @ref FR-002-002-003
     * @ref FR-002-002-004
     * 
     * @param p_fileName Filename.
     */
    EXPORTED_API explicit CtFileOutput(const CtString& p_fileName, WriteMode p_mode = WriteMode::Append);

    /**
     * @brief Destructor for CtFileOutput.
     *
     * @ref FR-002-002-005
     * 
     * Performs any necessary cleanup.
     */
    EXPORTED_API ~CtFileOutput();

    /**
     * @brief Set the the delimiter of write() method.
     *
     * @ref FR-002-002-006
     * 
     * @param p_delim The delimiter.
     * @param p_delim_size The delimiter size.
     */
    EXPORTED_API void setDelimiter(const char* p_delim, CtUInt8 p_delim_size);

    /**
     * @brief This method writes to file.
     *
     * @ref FR-002-002-007
     * @ref FR-002-002-008
     * @ref FR-002-002-010
     * 
     * @details
     * Use this method to write data one by one. After writing the data, the delimiter is written.
     * 
     * @param p_data The data to be written.
     * @return void
     */
    EXPORTED_API void write(CtRawData* p_data);

    /**
     * @brief This method writes to file.
     *
     * @ref FR-002-002-009
     * @ref FR-002-002-010
     * 
     * @details
     * Use this method to write data in batches. No delimiter is written.
     * 
     * @param p_data The data to be written.
     * @return void
     */
    EXPORTED_API void writePart(CtRawData* p_data);

private:
    std::ofstream m_file;               /**< File stream. */
    std::unique_ptr<char[]> m_delim;    /**< Batch write delimiter. */
    CtUInt8 m_delim_size;               /**< Delimeter size. */
};


#endif //INCLUDE_CTFILEOUTPUT_HPP_