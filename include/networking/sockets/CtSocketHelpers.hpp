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
 * @file CtSocketHelpers.hpp
 * @brief CtSocketHelpers class declaration that contains helpers for various sockets utilities.
 * @date 21-01-2024
 * 
 */

#ifndef INCLUDE_CTSOCKETHELPERS_HPP_
#define INCLUDE_CTSOCKETHELPERS_HPP_

#include "definitions.hpp"
#include "CtTypes.hpp"

#include "exceptions/CtNetworkExceptions.hpp"

#include <string>
#include <vector>

class CtSocketUdp;

/**
 * @class CtSocketHelpers
 * @brief A class contaning helpers for various sockets utilities.
 */
class CtSocketHelpers {
public:
    /**
     * @brief Set the Socket Timeout object
     * 
     * @param socketTimeout The target timeout for the poll request.
     */
    EXPORTED_API static void setSocketTimeout(int32_t socketTimeout);

    /**
     * @brief Get all available interfaces the device.
     */
    EXPORTED_API static std::vector<std::string> getInterfaces();

    /**
     * @brief Get address of a specific interface.
     * 
     * @param p_ifName The name of the interface.
     */
    EXPORTED_API static std::string interfaceToAddress(const std::string& p_ifName);

    /**
     * @brief Convert address to uin32_t
     * 
     * @param p_addr The address in form of std::string
     */
    EXPORTED_API static CtUInt32 getAddressAsUInt(const std::string& p_addr);

    /**
     * @brief Convert address to std::string
     * 
     * @param p_addr The address in form of CtUInt32
     */
    EXPORTED_API static std::string getAddressAsString(CtUInt32 p_addr);

private:
    static int32_t socketTimeout; /**< The timeout value for socket poll operations. */

    /**
     * @brief Set the Connection Timeout object
     * 
     * @param timeout 
     * @param timeout_ms 
     */
    static void setConnectionTimeout(timeval& timeout, CtUInt32 timeout_ms);

friend class CtSocketUdp;
};

#endif //INCLUDE_CTSOCKETHELPERS_HPP_
