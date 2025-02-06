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
 * @file CtSocketUdp.cpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#include "networking/CtSocketUdp.hpp"

CtSocketUdp::CtSocketUdp() {
    m_addrType = AF_INET;
    m_port = 0;
    m_socket = socket(m_addrType, SOCK_DGRAM, IPPROTO_UDP);
    if (m_socket == -1) {
        throw CtSocketError("Socket cannot be assigned.");
    }
    m_pollin_sockets[0].fd = m_socket;
    m_pollin_sockets[0].events = POLLIN;

    m_pollout_sockets[0].fd = m_socket;
    m_pollout_sockets[0].events = POLLOUT;
}

CtSocketUdp::~CtSocketUdp() {
    close(m_socket);
}

void CtSocketUdp::setSub(const CtString& p_interfaceName, CtUInt16 p_port) {
    memset(&m_subAddress, 0, sizeof(m_subAddress));
    m_subAddress.sin_family = m_addrType;
    m_subAddress.sin_addr.s_addr = CtSocketHelpers::getAddressAsUInt(CtSocketHelpers::interfaceToAddress(p_interfaceName));
    m_subAddress.sin_port = htons(p_port);

    if (bind(m_socket, (struct sockaddr*)&m_subAddress, sizeof(m_subAddress)) == -1) {
        throw CtSocketBindError(CtString("Socket bind to port ") + ToCtString(p_port) + CtString(" failed."));
    }
}

void CtSocketUdp::setPub(CtUInt16 p_port, const CtString& p_addr) {
    memset(&m_pubAddress, 0, sizeof(m_pubAddress));
    m_pubAddress.sin_family = m_addrType;
    m_pubAddress.sin_addr.s_addr = CtSocketHelpers::getAddressAsUInt(p_addr);
    m_pubAddress.sin_port = htons(p_port);
}

CtBool CtSocketUdp::pollRead() {
    int pollResult = poll(m_pollin_sockets, 1, CtSocketHelpers::socketTimeout);

    if (pollResult < 0) {
        throw CtSocketPollError("Socket polling-in failed.");
    } else if (pollResult == 0) {
        return CT_FALSE;
    } else {
        return CT_TRUE;
    }
}

CtBool CtSocketUdp::pollWrite() {
    int pollResult = poll(m_pollout_sockets, 1, CtSocketHelpers::socketTimeout);

    if (pollResult < 0) {
        throw CtSocketPollError("Socket polling-out failed.");
    } else if (pollResult == 0) {
        return CT_FALSE;
    } else {
        return CT_TRUE;
    }
}

void CtSocketUdp::send(CtUInt8* p_data, CtUInt32 p_size) {
    if (sendto(m_socket, p_data, p_size, MSG_DONTWAIT, (struct sockaddr*)&m_pubAddress, sizeof(m_pubAddress)) == -1) {
        throw CtSocketWriteError("Sending data via socket failed.");
    }
}

void CtSocketUdp::send(CtRawData& p_message) {
    send(p_message.get(), p_message.size());
}

void CtSocketUdp::receive(CtUInt8* p_data, CtUInt32 p_size, CtNetAddress* p_client) {
    sockaddr_in s_clientAddress_in;
    socklen_t s_clientAddressLength = sizeof(s_clientAddress_in);
    int bytesRead = recvfrom(m_socket, p_data, p_size, MSG_DONTWAIT, (struct sockaddr*)&s_clientAddress_in, &s_clientAddressLength);

    if (bytesRead == -1) {
        throw CtSocketReadError("Receiving data via socket failed.");
    }

    if (p_client != nullptr) {
        p_client->addr = (CtString)CtSocketHelpers::getAddressAsString(*(CtUInt32*)(&s_clientAddress_in.sin_addr));
        p_client->port = s_clientAddress_in.sin_port;
    }

    p_data[bytesRead] = '\0';
}

void CtSocketUdp::receive(CtRawData* p_message, CtNetAddress* p_client) {
    CtUInt8* s_buffer = new CtUInt8[p_message->maxSize()];
    receive(s_buffer, p_message->maxSize(), p_client);
    p_message->clone(s_buffer, p_message->maxSize());
    delete[] s_buffer;
}
