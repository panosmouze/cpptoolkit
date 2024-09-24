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
 * @file CtSocketUdp.hpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#ifndef INCLUDE_CTSOCKETUDP_HPP_
#define INCLUDE_CTSOCKETUDP_HPP_

#include "definitions.hpp"
#include "CtTypes.hpp"
#include "networking/sockets/CtSocketHelpers.hpp"

#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>

/**
 * @class CtSocketUdp
 * @brief A class representing a UDP socket wrapper.
 * 
 */
class CtSocketUdp {
public:

    /**
     * @brief Constructor for CtSocketUdp.
     * 
     */
    EXPORTED_API CtSocketUdp();

    /**
     * @brief Destructor for CtSocketUdp.
     * 
     */
    EXPORTED_API ~CtSocketUdp();

    /**
     * @brief Set the socket for subscribing.
     * @param p_interfaceName The interface name to bind to.
     * @param p_port The port to bind to.
     */
    EXPORTED_API void setSub(const std::string& p_interfaceName, uint16_t p_port);

    /**
     * @brief Set the socket for publishing.
     * @param p_port The port to send data to.
     * @param p_addr The address to send data to. Default to empty string.
     */
    EXPORTED_API void setPub(uint16_t p_port, const std::string& p_addr = "0.0.0.0");

    /**
     * @brief Check if there is data available to read.
     * 
     * @return True if data is available, false otherwise.
     */
    EXPORTED_API bool pollRead();

    /**
     * @brief Check if data can be written to the fd.
     * 
     * @return True if there is at least one byte available, false otherwise.
     */
    EXPORTED_API bool pollWrite();

    /**
     * @brief Send data over the socket.
     * @param p_data Buffer containing the data to sent.
     * @param p_size Size of the buffer.
     */
    EXPORTED_API void send(uint8_t* p_data, CtUInt32 p_size);

    /**
     * @brief Send data over the socket.
     * @param p_message Struct containing the message to sent.
     */
    EXPORTED_API void send(CtNetMessage& p_message);

    /**
     * @brief Receive data from the socket.
     * 
     * @param p_data Buffer containing the data to sent.
     * @param p_size Size of the buffer.
     * @param p_client Pointer to a CtNetAddress object to store the client's address (output parameter).
     */
    EXPORTED_API void receive(uint8_t* p_data, CtUInt32 p_size, CtNetAddress* p_client = nullptr);

    /**
     * @brief Receive data from the socket.
     * @param p_message Struct to store the message received.
     * @param p_clientAddress Pointer to a CtNetAddress object to store the client's address (output parameter).
     */
    EXPORTED_API void receive(CtNetMessage* p_message, CtNetAddress* p_clientAddress = nullptr);

private:
    int m_addrType;                         /**< The socket domain (IPv4 or IPv6). */
    int m_socket;                           /**< The socket descriptor. */
    uint16_t m_port;                        /**< The port associated with the socket. */
    std::string m_addr;                     /**< The address associated with the socket. */
    struct pollfd m_pollin_sockets[1];      /**< Array for polling-in file descriptors. */
    struct pollfd m_pollout_sockets[1];     /**< Array for polling-out file descriptors. */
    sockaddr_in m_pubAddress;               /**< The address for publishing data. */
    sockaddr_in m_subAddress;               /**< The address for subscribing to data. */
};

#endif //INCLUDE_CTSOCKETUDP_HPP_
