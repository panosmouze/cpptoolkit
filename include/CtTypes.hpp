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
 * @file CtTypes.hpp
 * @brief Header file for basic types and classes.
 * @date 21-01-2024
 * 
 */

#ifndef INCLUDE_CTTYPES_HPP_
#define INCLUDE_CTTYPES_HPP_

#include "definitions.hpp"
#include "exceptions/CtTypeExceptions.hpp"

#include <stdint.h>
#include <string>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

/**
 * @brief Typedefs for basic types.
 * 
 */
#define CtUInt8 uint8_t
#define CtUInt16 uint16_t
#define CtUInt32 uint32_t
#define CtUInt64 uint64_t

#define CtInt8 int8_t
#define CtInt16 int16_t
#define CtInt32 int32_t
#define CtInt64 int64_t

#define CtChar char

/**
 * @brief Default buffer size
 * 
 */
#define CT_BUFFER_SIZE 2048

/**
 * @brief CtString class extends the std::string class. It provides additional methods for string manipulation.
 * 
 */
class CtString : public std::string {
public:
    using std::string::string;

    /**
     * @brief CtString constructor.
     * 
     * @param str The string to be used.
     */
    explicit CtString(const std::string& str) : std::string(str) {}

    /**
     * @brief This method splits the string into substrings using the given delimiter.
     * 
     * @param delimiter This is the delimiter that will be used to split the string.
     * @param result The vector that will contain the substrings.
     */
    void split(char delimiter, std::vector<CtString> *result) const {
        std::string::size_type start = 0;
        auto end = find(delimiter);

        while (end != std::string::npos) {
            result->push_back((CtString)trim(substr(start, end - start)));
            start = end + 1;
            end = find(delimiter, start);
        }
        
        result->push_back((CtString)trim(substr(start)));
    }

    /**
     * @brief This method trims the string from the left and right side.
     * 
     * @param s The string to be trimmed.
     * @return CtString The trimmed string.
     */
    CtString trim(const std::string& s) const {
        auto start = s.find_first_not_of(" \t\n");
        auto end = s.find_last_not_of(" \t\n");
        return (CtString)((start == std::string::npos) ? "" : s.substr(start, end - start + 1));
    }
};

/**
 * @brief Struct describing a network address.
 * @details
 * The network address is described by the IP address and the port number.
 * 
 */
typedef struct _CtNetAddress {
    CtString addr;
    CtUInt16 port;
} CtNetAddress;

/**
 * @brief Struct describing raw data buffer.
 * 
 * @details
 * The default buffer size is defined as CT_BUFFER_SIZE bytes.
 * The buffer can be set either by another buffer object or given the size of the buffer.
 * The buffer has a prespecified size that can be filled with bytes. It can monitor the 
 * size of the buffer that it is currently used and it ensures that the buffer will not 
 * overflow. If an overflow occurs an exception will be thrown - CtOutOfRangeError().
 * 
 * @code {.cpp}
 * CtRawData data;
 * data.nextByte('a');
 * data.nextByte('b');
 * data.nextByte('c');
 * CtUInt8* buffer = data.get(); // returns "abc"
 * data.removeNLastBytes(1);
 * buffer = data.get(); // returns "ab"
 * data.reset(); // resets the buffer
 * buffer = data.get(); // returns ""
 * @endcode 
 */
class CtRawData {
public:

    /**
     * @brief CtRawData constructor.
     * 
     * @param p_size The size of the buffer. The default size is defined as CT_BUFFER_SIZE bytes. 
     */
    EXPORTED_API explicit CtRawData(CtUInt32 p_size = CT_BUFFER_SIZE) : m_maxSize(p_size) {
        m_data = new CtUInt8[m_maxSize];
        m_size = 0;
    };

    /**
     * @brief CtRawData copy constructor.
     * 
     * @param p_data Another CtRawData object that it is used to init the currently created.
     */
    EXPORTED_API CtRawData(CtRawData& p_data) : m_maxSize(p_data.maxSize()) {
        m_data = new CtUInt8[m_maxSize];
        clone(p_data);
    };

    /**
     * @brief Destructor.
     * 
     */
    EXPORTED_API virtual ~CtRawData() {
        delete[] m_data;
    }

    /**
     * @brief Sets the next byte of the buffer. It also raises the size of the buffer.
     *      If the buffer is full an exception will be thrown - CtOutOfRangeError()
     * 
     * @param byte The byte to be added.
     * @return void 
     */
    EXPORTED_API void nextByte(char byte) {
        if (m_size < m_maxSize) {
            m_data[m_size++] = byte;
        }
    }

    /**
     * @brief This method returns a pointer to the last N bytes of the buffer.
     *    If the number of bytes is greater than the buffer size an exception will be thrown - CtOutOfRangeError()
     * 
     * @param p_num Number of bytes to be returned.
     * @return CtUInt8* Pointer to the last N bytes of the buffer.
     */
    EXPORTED_API CtUInt8* getNLastBytes(CtUInt32 p_num) {
        if (p_num > m_size) {
            throw CtOutOfRangeError("Data size is out of range.");
        }
        return &m_data[m_size - p_num];
    }

    /**
     * @brief This method removes the last N bytes of the buffer. It also reduces the size of the buffer.
     *   If the number of bytes is greater than the buffer size an exception will be thrown - CtOutOfRangeError()
     * 
     * @param p_num Number of bytes to be returned.
     * @return EXPORTED_API 
     */
    EXPORTED_API void removeNLastBytes(CtUInt32 p_num) {
        if (p_num > m_size) {
            throw CtOutOfRangeError("Data size is out of range.");
        }
        m_size -= p_num;
    }

    /**
     * @brief The actual size of the buffer.
     * 
     * @return CtUInt32 The actual size of the buffer.
     */
    EXPORTED_API CtUInt32 size() {
        return m_size;
    }

    /**
     * @brief The max size of the buffer.
     * 
     * @return CtUInt32 The max size of the buffer.
     */
    EXPORTED_API CtUInt32 maxSize() {
        return m_maxSize;
    }

    /**
     * @brief This method returns a pointer to the buffer data.
     * 
     * @return CtUInt8* Pointer to the buffer data. 
     */
    EXPORTED_API CtUInt8* get() {
        return m_data;
    }

    /**
     * @brief This method fills the buffer with the data given in the parameters.
     *   This method overwrites the buffer and the actual size. The maximum size of the buffer is preserved.
     *   If the size of the data is greater than the buffer size an exception will be thrown - CtOutOfRangeError()
     * 
     * @param p_data A pointer to the data to be cloned.
     * @param p_size The size of the gven buffer.
     * @return void
     */
    EXPORTED_API void clone(const CtUInt8* p_data, CtUInt32 p_size) {
        if (p_size > m_maxSize) {
            throw CtOutOfRangeError("Data size is out of range.");
        }
        m_size = p_size;
        memcpy(m_data, p_data, p_size);
    }


    /**
     * @brief This method fills the buffer with the data given in the parameters.
     *   This method overwrites the buffer and the actual size. The maximum size of the buffer is preserved.
     *   If the size of the data is greater than the buffer size an exception will be thrown - CtOutOfRangeError()
     * 
     * @param p_data A CtRawData object to be cloned.
     * @return void
     */
    EXPORTED_API void clone(CtRawData& p_data) {
        if (p_data.size() > m_maxSize) {
            throw CtOutOfRangeError("Data size is out of range.");
        }
        m_size = p_data.size();
        memcpy(m_data, p_data.get(), p_data.size());
    }

    /**
     * @brief This method resets the buffer to 0 size. The allocated memory is not freed.
     *   The actual size of the buffer is set to 0.
     * 
     * @return void 
     */
    EXPORTED_API void reset() {
        m_size = 0;
    }

    /**
     * @brief Assignment operator for CtRawData.
     * Copies the data from a CtRawData to another CtRawData object.
     * 
     * @param other The CtRawData object to copy.
     * 
     * @return CtRawData& Reference to the current CtRawData object.
     */
    EXPORTED_API CtRawData& operator=(CtRawData& other) {
        if (this != &other) {
            clone(other);
        }
        return *this;
    }

private:
    CtUInt8* m_data;                            /*!< The buffer data. */
    CtUInt32 m_size;                            /*!< The actual size of the buffer. */
    const CtUInt32 m_maxSize;                   /*!< The maximum size of the buffer. */
};

#endif //INCLUDE_CTTYPES_HPP_
