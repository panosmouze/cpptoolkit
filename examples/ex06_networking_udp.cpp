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
 * @file ex07_networking_udp.cpp
 * @brief In this example 2 workers are implemented. Both of them open a udp socket.
 *          The first one waits to receive a message and thens sends a response.
 *          The second one sends a broadcast message and then waits to receive something back.
 * @date 18-01-2024
 * 
 */

#include "cpptoolkit.hpp"

#include <iostream>

#define INTF    "lo"
#define W1_PORT 5041
#define W2_PORT 5042

typedef struct _DummyData {
    CtUInt8 id;
    CtChar name[25];
} DummyData;

void worker1Func();
void worker2Func();

int main() {
    CtSocketHelpers::setSocketTimeout(-1);

    CtWorker worker1;
    worker1.setTaskFunc(worker1Func);

    CtWorker worker2;
    worker2.setTaskFunc(worker2Func);

    worker1.runTask();

    CtThread::sleepFor(1000); // wait for a while in order to be sure that "server" started
    worker2.runTask();

    worker1.joinTask();
    worker2.joinTask();

    return 0;
}

void worker1Func() {
    /* Create socket */
    CtSocketUdp socket1;
    socket1.setSub(INTF, W1_PORT);
    socket1.setPub(W2_PORT);

    /* Wait for incoming msg */
    while(true) {
        if (socket1.pollRead()) {
            CtRawData msg;
            socket1.receive(&msg);
            DummyData* data = (DummyData*)msg.get();
            std::cout << ("receive data from id: " + std::to_string(data->id) + ", name: " + data->name) << std::endl;


            /* Send response msg */
            while(true) {
                if (socket1.pollWrite()) {
                    DummyData data = {1, "bob"};
                    socket1.send((CtUInt8*)&data, sizeof(DummyData));
                    break;
                }
            }
            break;
        }
    }
}

void worker2Func() {
    /* Create socket */
    CtSocketUdp socket2;
    socket2.setSub(INTF, W2_PORT);
    socket2.setPub(W1_PORT);

    /* Send msg */
    while(true) {
        if (socket2.pollWrite()) {
            DummyData data = {2, "alice"};
            socket2.send((CtUInt8*)&data, sizeof(DummyData));

            /* Wait response msg */
            while(true) {
                if (socket2.pollRead()) {
                    CtRawData msg;
                    socket2.receive(&msg);
                    DummyData* data = (DummyData*)msg.get();
                    std::cout << ("receive data from id: " + std::to_string(data->id) + ", name: " + data->name) << std::endl;
                    break;
                }
            }
            break;
        }
    }
}
