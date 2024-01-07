/*
 * CtConfigParser.hpp
 *
 *  Created on: Nov 13, 2023
 *      Author: Mouzenidis Panagiotis
 */

#ifndef INCLUDE_IO_CTCONFIGPARSER_HPP_
#define INCLUDE_IO_CTCONFIGPARSER_HPP_

#include "definitions.hpp"

#include <string>
#include <map>

/**
 * @class CtConfigParser
 * @brief A configuration file parser class for extracting various data types from configuration values.
 */
class CtConfigParser {
public:
    /**
     * @brief Constructor for CtConfigParser.
     *          This constructor can throw CtFileParseError if file cannot be parsed.
     *          This constructor can throw CtFileError if there is a problem with the file.
     * 
     * @param configFile The path to the configuration file to be parsed.
     */
    EXPORTED_API explicit CtConfigParser(const std::string& configFile);

    /**
     * @brief Destructor for cleaning up resources.
     */
    EXPORTED_API ~CtConfigParser();

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

private:
    std::string m_configFile; /**< The path to the configuration file. */
    std::map<std::string, std::string> m_configValues; /**< A map to store configuration key-value pairs. */
};

#endif // INCLUDE_IO_CTCONFIGPARSER_HPP_
