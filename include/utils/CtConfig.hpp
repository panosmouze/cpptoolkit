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
 * @file CtConfig.hpp
 * @brief CtConfig class header file.
 * @date 10-03-2024
 * 
 */

#ifndef INCLUDE_CTCONFIG_HPP_
#define INCLUDE_CTCONFIG_HPP_

#include "core.hpp"

#include "io/CtFileOutput.hpp"
#include "io/CtFileInput.hpp"

/**
 * @class CtConfig
 * @brief A configuration file parser class for extracting various data types from configuration values.
 * 
 * @details
 * The CtConfig class provides a mechanism for reading and writing configuration files providing key-value
 * pairs of various data types. The class can parse integer, unsigned integer, CtFloat, CtDouble, and string values.
 * The class is thread-safe and can be used in multi-threaded environments.
 */
class CtConfig {
public:
    /**
     * @brief Constructor for CtConfig.
     * 
     * @ref FR-004-001-001
     * 
     * @param configFile The path to the configuration file to be parsed.
     */
    EXPORTED_API explicit CtConfig(const CtString& p_configFile);

    /**
     * @brief Destructor for cleaning up resources.
     * 
     * @ref FR-004-001-002
     */
    EXPORTED_API ~CtConfig();

    /**
     * @brief Read data from config file. 
     *          This method can throw CtFileParseError if file cannot be parsed.
     *          This method can throw CtFileError if there is a problem with the file.
     * 
     * @ref FR-004-001-006
     * @ref FR-004-001-009
     * @ref FR-004-001-007
     */
    EXPORTED_API void read();

    /**
     * @brief Write data to config file.
     * 
     * @ref FR-004-001-005
     * @ref FR-004-001-008
     */
    EXPORTED_API void write();

    /**
     * @brief Parse a value as a 32-bit signed integer or 
     *          throw CtKeyNotFoundError if key is not found in the map or
     *          throw CtParseError if key value cannot be parsed as int.
     * 
     * @ref FR-004-001-010
     * @ref FR-004-001-003
     * @ref FR-004-001-013
     * 
     * @param key The key value to be parsed.
     * @return The parsed integer value.
     */
    EXPORTED_API CtInt32 parseAsInt(const CtString& p_key);

    /**
     * @brief Parse a value as a 32-bit unsigned integer or 
     *          throw CtKeyNotFoundError if key is not found in the map or
     *          throw CtParseError if key value cannot be parsed as uint.
     * 
     * @ref FR-004-001-010
     * @ref FR-004-001-003
     * @ref FR-004-001-013
     * 
     * @param key The key value to be parsed.
     * @return The parsed unsigned integer value.
     */
    EXPORTED_API CtUInt32 parseAsUInt(const CtString& p_key);

    /**
     * @brief Parse a value as a CtFloat or 
     *          throw CtKeyNotFoundError if key is not found in the map or
     *          throw CtParseError if key value cannot be parsed as CtFloat.
     * 
     * @ref FR-004-001-010
     * @ref FR-004-001-003
     * @ref FR-004-001-013
     * 
     * @param key The key value to be parsed.
     * @return The parsed floating-point value.
     */
    EXPORTED_API CtFloat parseAsFloat(const CtString& p_key);

    /**
     * @brief Parse a value as a CtDouble-precision floating-point number or 
     *          throw CtKeyNotFoundError if key is not found in the map or
     *          throw CtParseError if key value cannot be parsed as CtDouble.
     * 
     * @ref FR-004-001-010
     * @ref FR-004-001-003
     * @ref FR-004-001-013
     * 
     * @param key The key value to be parsed.
     * @return The parsed CtDouble value.
     */
    EXPORTED_API CtDouble parseAsDouble(const CtString& p_key);

    /**
     * @brief Parse a value as a standard C++ string or 
     *          throw CtKeyNotFoundError if key is not found in the map.
     * 
     * @ref FR-004-001-010
     * @ref FR-004-001-003
     * 
     * @param key The key value to be parsed.
     * @return The parsed string.
     */
    EXPORTED_API CtString parseAsString(const CtString& p_key);
    
    /**
     * @brief Write value to key as int.
     * 
     * @ref FR-004-001-011
     * @ref FR-004-001-003
     * 
     * @param p_key The key value.
     * @param p_value The value to be written for this key.
     */
    EXPORTED_API void writeInt(const CtString& p_key, const CtInt32& p_value);

    /**
     * @brief Write value to key as uint.
     * 
     * @ref FR-004-001-011
     * @ref FR-004-001-003
     * 
     * @param p_key The key value.
     * @param p_value The value to be written for this key.
     */
    EXPORTED_API void writeUInt(const CtString& p_key, const CtUInt32& p_value);

    /**
     * @brief Write value to key as CtFloat.
     * 
     * @ref FR-004-001-011
     * @ref FR-004-001-003
     * 
     * @param p_key The key value.
     * @param p_value The value to be written for this key.
     */
    EXPORTED_API void writeFloat(const CtString& p_key, const CtFloat& p_value);

    /**
     * @brief Write value to key as CtDouble.
     * 
     * @ref FR-004-001-011
     * @ref FR-004-001-003
     * 
     * @param p_key The key value.
     * @param p_value The value to be written for this key.
     */
    EXPORTED_API void writeDouble(const CtString& p_key, const CtDouble& p_value);

    /**
     * @brief Write value to key as string.
     * 
     * @ref FR-004-001-011
     * @ref FR-004-001-003
     * 
     * @param p_key The key value.
     * @param p_value The value to be written for this key.
     */
    EXPORTED_API void writeString(const CtString& p_key, const CtString& p_value);

    /**
     * @brief This method resets the configuration values.
     * 
     * @ref FR-004-001-014 
     * 
     * @return void  
     */
    EXPORTED_API void reset();

private:
    /**
     * @brief This method returns the value assosiated with the given key or 
     *          throw CtKeyNotFoundError if key is not found in the map.
     * 
     * @ref FR-004-001-004
     * @ref FR-004-001-012
     * 
     * @param key The key value to be parsed.
     * @return CtString The string value assosiated with the given key.
     */
    CtString getValue(const CtString& p_key);

    /**
     * @brief This method gets a line as input and parse it in order to find the key and value
     *          of configured item. These values are stored in the CtMap m_configValues.
     *          This method can throw CtFileParseError if file cannot be parsed.
     * 
     * @ref FR-004-001-006
     * @ref FR-004-001-009
     * 
     * @param line 
     */
    void parseLine(const CtString& p_line);

private:
    CtMutex m_mtx_control;                      /*!< Internal mutex for synchronization. */
    CtFileInput* m_source;                      /*!< The source file for reading configuration values. */
    CtFileOutput* m_sink;                       /*!< The sink file for writing configuration values. */
    CtString m_configFile;                      /*!< The path to the configuration file. */
    CtMap<CtString, CtString> m_configValues;   /*!< A map to store configuration key-value pairs. */
};

#endif //INCLUDE_CTCONFIG_HPP_