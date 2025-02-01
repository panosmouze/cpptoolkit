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
 * @file CtHelpers.cpp
 * @brief 
 * @date 31-01-2025
 * 
 */

#include "core/CtHelpers.hpp"

#include "core/exceptions/CtTypeExceptions.hpp"
#include "core/exceptions/CtNetworkExceptions.hpp"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <ifaddrs.h>

void CtStringHelpers::split(const CtString& p_string, CtChar p_delimiter, CtVector<CtString> *p_result) {
    CtString::size_type s_start = 0;
    auto s_end = p_string.find(p_delimiter);

    while (s_end != CtString::npos) {
        p_result->push_back(trim(p_string.substr(s_start, s_end - s_start)));
        s_start = s_end + 1;
        s_end = p_string.find(p_delimiter, s_start);
    }
    
    p_result->push_back(trim(p_string.substr(s_start)));
}


CtString CtStringHelpers::trim(const CtString& p_string) {
    auto s_start = p_string.find_first_not_of(" \t\n");
    auto s_end = p_string.find_last_not_of(" \t\n");
    return ((s_start == CtString::npos) ? "" : p_string.substr(s_start, s_end - s_start + 1));
}

CtDouble CtStringHelpers::StrToDouble(const CtString& p_string) {
    CtDouble parsed_value;
    try {
        parsed_value = stod(p_string);
    } catch (...) {
        throw CtTypeParseError(p_string + CtString(" can not be parsed as CtDouble."));
    }
    return parsed_value;
}

CtFloat CtStringHelpers::StrToFloat(const CtString& p_string) {
    CtDouble parsed_value;
    try {
        parsed_value = stof(p_string);
    } catch (...) {
        throw CtTypeParseError(p_string + CtString(" can not be parsed as CtFloat."));
    }
    return parsed_value;
}

CtUInt32 CtStringHelpers::StrToUInt(const CtString& p_string) {
    CtUInt32 parsed_value;
    try {
        parsed_value = stoul(p_string);
    } catch (...) {
        throw CtTypeParseError(p_string + CtString(" can not be parsed as uint."));
    }
    return parsed_value;
}

CtInt32 CtStringHelpers::StrToInt(const CtString& p_string) {
    CtInt32 parsed_value;
    try {
        parsed_value = stoi(p_string);
    } catch (...) {
        throw CtTypeParseError(p_string + CtString(" can not be parsed as int."));
    }
    return parsed_value;
}

void CtSocketHelpers::setSocketTimeout(CtInt32 p_socketTimeout) {
    CtSocketHelpers::socketTimeout = p_socketTimeout;
}

CtVector<CtString> CtSocketHelpers::getInterfaces() {
    struct ifaddrs *s_ifaddr, *s_ifa;
    CtVector<CtString> s_interfaces;

    if (getifaddrs(&s_ifaddr) == -1) {
        throw CtSocketError("Cannot get interfaces.");
    }

    for (s_ifa = s_ifaddr; s_ifa != nullptr; s_ifa = s_ifa->ifa_next) {
        s_interfaces.push_back(CtString(s_ifa->ifa_name));
    }
    return s_interfaces;
}

CtString CtSocketHelpers::interfaceToAddress(const CtString& p_ifName) {
    struct ifaddrs *ifaddr, *ifa;

    if (getifaddrs(&ifaddr) == -1) {
        throw CtSocketError("Cannot get interfaces.");
    }

    for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
        if (CtString(ifa->ifa_name) == p_ifName) {
            if (ifa->ifa_addr == nullptr) {
                freeifaddrs(ifaddr);
                throw CtSocketError("Not valid interface entered.");
            }

            if (ifa->ifa_addr->sa_family == AF_INET) {
                CtChar ipBuffer[INET_ADDRSTRLEN];
                sockaddr_in* sockAddr = reinterpret_cast<sockaddr_in*>(ifa->ifa_addr);

                if (inet_ntop(AF_INET, &(sockAddr->sin_addr), ipBuffer, INET_ADDRSTRLEN) == nullptr) {
                    freeifaddrs(ifaddr);
                    throw CtSocketError("Failed to convert IPv4 address.");
                }

                freeifaddrs(ifaddr);
                return ipBuffer;
            }
        }
    }

    freeifaddrs(ifaddr);
    throw CtSocketError("Not valid interface found.");
}

CtUInt32 CtSocketHelpers::getAddressAsUInt(const CtString& p_addr) {
    CtUInt32 result = inet_addr(p_addr.c_str());

    if (result == INADDR_NONE) {
        throw CtSocketError("Invalid address given.");
    }

    return result;
};

CtString CtSocketHelpers::getAddressAsString(CtUInt32 p_addr) {
    CtChar result[INET_ADDRSTRLEN];

    if (inet_ntop(AF_INET, &p_addr, result, INET_ADDRSTRLEN) == nullptr) {
        throw CtSocketError("Failed to convert IPv4 address.");
    }

    return CtString(result);
};
