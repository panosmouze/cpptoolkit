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
 * @file CtSocketHelpers.cpp
 * @brief 
 * @date 21-01-2024
 * 
 */

#include "networking/sockets/CtSocketHelpers.hpp"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <ifaddrs.h>

int32_t CtSocketHelpers::socketTimeout = 0;

void CtSocketHelpers::setSocketTimeout(int32_t p_socketTimeout) {
    CtSocketHelpers::socketTimeout = p_socketTimeout;
}

std::vector<std::string> CtSocketHelpers::getInterfaces() {
    struct ifaddrs *s_ifaddr, *s_ifa;
    std::vector<std::string> s_interfaces;

    if (getifaddrs(&s_ifaddr) == -1) {
        throw CtSocketError("Cannot get interfaces.");
    }

    for (s_ifa = s_ifaddr; s_ifa != nullptr; s_ifa = s_ifa->ifa_next) {
        s_interfaces.push_back(std::string(s_ifa->ifa_name));
    }
    return s_interfaces;
}

std::string CtSocketHelpers::interfaceToAddress(const std::string& p_ifName) {
    struct ifaddrs *ifaddr, *ifa;

    if (getifaddrs(&ifaddr) == -1) {
        throw CtSocketError("Cannot get interfaces.");
    }

    for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
        if (std::string(ifa->ifa_name) == p_ifName) {
            if (ifa->ifa_addr == nullptr) {
                freeifaddrs(ifaddr);
                throw CtSocketError("Not valid interface entered.");
            }

            if (ifa->ifa_addr->sa_family == AF_INET) {
                char ipBuffer[INET_ADDRSTRLEN];
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

uint32_t CtSocketHelpers::getAddressAsUInt(const std::string& p_addr) {
    uint32_t result = inet_addr(p_addr.c_str());

    if (result == INADDR_NONE) {
        throw CtSocketError("Invalid address given.");
    }

    return result;
};

std::string CtSocketHelpers::getAddressAsString(uint32_t p_addr) {
    char result[INET_ADDRSTRLEN];

    if (inet_ntop(AF_INET, &p_addr, result, INET_ADDRSTRLEN) == nullptr) {
        throw CtSocketError("Failed to convert IPv4 address.");
    }

    return std::string(result);
};

void CtSocketHelpers::setConnectionTimeout(timeval& timeout, uint32_t timeout_ms) {
    timeout.tv_sec = timeout_ms/1000;
    timeout.tv_usec = 1000*(timeout_ms%1000);
};
