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
 * @file CtHelpers.hpp
 * @brief CtHelpers contains helpers for various utilities.
 * @date 31-01-2025
 * 
 */

#ifndef INCLUDE_CTHELPERS_HPP_
#define INCLUDE_CTHELPERS_HPP_

#include "core/definitions.hpp"
#include "core/CtTypes.hpp"

#define ToCtString(x) std::to_string(x) /**< Convert a number to a string. */

/**
 * @brief This namespace contains string helper functions.
 * 
 */
namespace CtStringHelpers {
    /**
     * @brief This method splits the string into substrings using the given delimiter.
     * 
     * @param p_string The string to be split.
     * @param p_delimiter This is the delimiter that will be used to split the string.
     * @param p_result The vector that will contain the substrings.
     */
    EXPORTED_API void split(const CtString& p_string, char p_delimiter, CtVector<CtString> *p_result);

    /**
     * @brief This method trims the string from the left and right side.
     * 
     * @param p_string The string to be trimmed.
     * @return CtString The trimmed string.
     */
    EXPORTED_API CtString trim(const CtString& p_string);

    /**
     * @brief This method converts a string to a CtDouble.
     * 
     * @details
     * If the string can not be converted to a CtDouble, a CtTypeParseError exception is thrown.
     * 
     * @param p_str The string to be converted.
     * @return CtDouble The converted CtDouble.
     */
    EXPORTED_API CtDouble StrToDouble(const CtString& p_str);

    /**
     * @brief This method converts a string to a CtFloat.
     * 
     * @details
     * If the string can not be converted to a CtFloat, a CtTypeParseError exception is thrown.
     * 
     * @param p_str The string to be converted.
     * @return CtFloat The converted CtFloat.
     */
    EXPORTED_API CtFloat StrToFloat(const CtString& p_str);

    /**
     * @brief This method converts a string to a CtUInt32.
     * 
     * @details
     * If the string can not be converted to a CtUInt32, a CtTypeParseError exception is thrown.
     * 
     * @param p_str The string to be converted.
     * @return CtUInt32 The converted CtUInt32.
     */
    EXPORTED_API CtUInt32 StrToUInt(const CtString& p_str);

    /**
     * @brief This method converts a string to a CtInt32.
     * 
     * @details
     * If the string can not be converted to a CtInt32, a CtTypeParseError exception is thrown.
     * 
     * @param p_str The string to be converted.
     * @return CtInt32 The converted CtInt32.
     */
    EXPORTED_API CtInt32 StrToInt(const CtString& p_str);
};

/**
 * @brief This namespace contains socket helper functions.
 * 
 */
namespace CtSocketHelpers {
    static CtInt32 socketTimeout = 0; /**< The timeout value for socket poll operations. */

    /**
     * @brief Set the Socket Timeout object
     * 
     * @param socketTimeout The target timeout for the poll request.
     */
    EXPORTED_API void setSocketTimeout(CtInt32 socketTimeout);

    /**
     * @brief Get all available interfaces the device.
     * 
     * @return CtVector<CtString> The available interfaces.
     */
    EXPORTED_API CtVector<CtString> getInterfaces();

    /**
     * @brief Get address of a specific interface.
     * 
     * @param p_ifName The name of the interface.
     * @return CtString The address of the interface.
     */
    EXPORTED_API CtString interfaceToAddress(const CtString& p_ifName);

    /**
     * @brief Convert address to uin32_t
     * 
     * @param p_addr The address in form of CtString
     * @return CtUInt32 The address in form of CtUInt32
     */
    EXPORTED_API CtUInt32 getAddressAsUInt(const CtString& p_addr);

    /**
     * @brief Convert address to CtString
     * 
     * @param p_addr The address in form of CtUInt32
     * @return CtString The address in form of CtString
     */
    EXPORTED_API CtString getAddressAsString(CtUInt32 p_addr);
};

#endif //INCLUDE_CTHELPERS_HPP_