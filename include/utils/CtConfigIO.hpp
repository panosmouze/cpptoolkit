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
 * @file CtConfigIO.hpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#ifndef INCLUDE_CTCONFIGIO_HPP_
#define INCLUDE_CTCONFIGIO_HPP_

#include "definitions.hpp"

#include "io/sources/CtTextFileSource.hpp"

#include <fstream>
#include <string>
#include <map>

/**
 * @class CtConfigIO
 * @brief A configuration file parser class for extracting various data types from configuration values.
 */
class CtConfigIO {
public:
    enum class CtConfigIOState {
        IDLE,
        READING,
        WRITING
    };

    /**
     * @brief Constructor for CtConfigIO.
     * @param configFile The path to the configuration file to be parsed.
     */
    EXPORTED_API explicit CtConfigIO(const std::string& configFile);

    /**
     * @brief Destructor for cleaning up resources.
     */
    EXPORTED_API ~CtConfigIO();

    EXPORTED_API void join();

    /**
     * @brief Read data from config file. 
     *          This method can throw CtFileParseError if file cannot be parsed.
     *          This method can throw CtFileError if there is a problem with the file.
     */
    EXPORTED_API CtConfigIO& read();

    /**
     * @brief Write data to config file.
     */
    EXPORTED_API CtConfigIO& write();

    /**
     * @brief Parse a value as a 32-bit signed integer or 
     *          throw CtKeyNotFoundError if key is not found in the map or
     *          throw CtParseError if key value cannot be parsed as int.
     * 
     * @param key The key value to be parsed.
     * @return The parsed integer value.
     */
    EXPORTED_API int32_t parseAsInt(const std::string& key);

    /**
     * @brief Parse a value as a 32-bit unsigned integer or 
     *          throw CtKeyNotFoundError if key is not found in the map or
     *          throw CtParseError if key value cannot be parsed as uint.
     * 
     * @param key The key value to be parsed.
     * @return The parsed unsigned integer value.
     */
    EXPORTED_API uint32_t parseAsUInt(const std::string& key);

    /**
     * @brief Parse a value as a float or 
     *          throw CtKeyNotFoundError if key is not found in the map or
     *          throw CtParseError if key value cannot be parsed as float.
     * 
     * @param key The key value to be parsed.
     * @return The parsed floating-point value.
     */
    EXPORTED_API float parseAsFloat(const std::string& key);

    /**
     * @brief Parse a value as a double-precision floating-point number or 
     *          throw CtKeyNotFoundError if key is not found in the map or
     *          throw CtParseError if key value cannot be parsed as double.
     * 
     * @param key The key value to be parsed.
     * @return The parsed double value.
     */
    EXPORTED_API double parseAsDouble(const std::string& key);

    /**
     * @brief Parse a value as a standard C++ string or 
     *          throw CtKeyNotFoundError if key is not found in the map.
     * 
     * @param key The key value to be parsed.
     * @return The parsed string.
     */
    EXPORTED_API std::string parseAsString(const std::string& key);
    
    /**
     * @brief Write value to key as int.
     * 
     * @param p_key The key value.
     * @param p_value The value to be written for this key.
     */
    EXPORTED_API void writeInt(const std::string& p_key, const int32_t& p_value);

    /**
     * @brief Write value to key as uint.
     * 
     * @param p_key The key value.
     * @param p_value The value to be written for this key.
     */
    EXPORTED_API void writeUInt(const std::string& p_key, const uint32_t& p_value);

    /**
     * @brief Write value to key as float.
     * 
     * @param p_key The key value.
     * @param p_value The value to be written for this key.
     */
    EXPORTED_API void writeFloat(const std::string& p_key, const float& p_value);

    /**
     * @brief Write value to key as double.
     * 
     * @param p_key The key value.
     * @param p_value The value to be written for this key.
     */
    EXPORTED_API void writeDouble(const std::string& p_key, const double& p_value);

    /**
     * @brief Write value to key as string.
     * 
     * @param p_key The key value.
     * @param p_value The value to be written for this key.
     */
    EXPORTED_API void writeString(const std::string& p_key, const std::string& p_value);

public:
    /**
     * @brief Max number of characters per line in configuration file.
     * 
     */
    static uint32_t maxNumberOfCharacters;

private:
    /**
     * @brief This method returns the value assosiated with the given key or 
     *          throw CtKeyNotFoundError if key is not found in the map.
     * 
     * @param key The key value to be parsed.
     * @return std::string The string value assosiated with the given key.
     */
    std::string getValue(const std::string& key);

    /**
     * @brief This method gets a line as input and parse it in order to find the key and value
     *          of configured item. These values are stored in the std::map m_configValues.
     *          This method can throw CtFileParseError if file cannot be parsed.
     * 
     * @param line 
     */
    void parseLine(const std::string& line);

    void setState(CtConfigIOState p_state);
    CtConfigIOState getState();
    bool isAvailable();

private:
    std::mutex m_mtx_control; ///< Internal mutex for synchronization.
    std::atomic<CtConfigIOState> m_state;
    CtTextFileSource* s_source;
    std::string m_configFile; /**< The path to the configuration file. */
    std::map<std::string, std::string> m_configValues; /**< A map to store configuration key-value pairs. */
};

#endif //INCLUDE_CTCONFIGIO_HPP_
