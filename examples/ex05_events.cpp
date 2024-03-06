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
 * @file ex06_events.cpp
 * @brief 
 * @date 03-02-2024
 * 
 */

#include "CtUtils.hpp"
#include "CtThreading.hpp"

#include <iostream>

// implement a CtObject class
class CtMainPage : public CtObject {
public: 
    // Create a list of custom events
    enum MyEvents : uint8_t {
        EVENT1 = 1,
        EVENT2 = 2,
        EVENT3 = 3
    };

    CtMainPage() {
        // register events to CtObject
        registerEvent(EVENT1);
        registerEvent(EVENT2);
        registerEvent(EVENT3);
    }

    ~CtMainPage() {

    }

    void test1() {
        // code for test1 func

        // trigger for EVENT1
        triggerEvent(EVENT1);
    }

    void test2() {
        // code for test2 func
        
        // trigger for EVENT2
        triggerEvent(EVENT2);
    }
};

void callback(int idx) {
    std::cout << "EVENT1-3 executed with id: " + std::to_string(idx) << std::endl;
}

int main() {
    CtMainPage page;
    CtTask task1, task2;
    task1.setTaskFunc([](){std::cout << "EVENT1-1 executed" << std::endl;});
    task2.setTaskFunc([](){std::cout << "EVENT1-2 executed" << std::endl;});

    // use of connectEvent
    page.connectEvent(CtMainPage::EVENT1, task1);

    // use static definition of connectEvent
    CtObject::connectEvent(&page, CtMainPage::EVENT1, task2);

    // use of connectEvent given a lamda function
    page.connectEvent(CtMainPage::EVENT2, []{std::cout << "EVENT2-1 executed" << std::endl;});

    // use of connectEvent given a normal function
    page.connectEvent(CtMainPage::EVENT1, callback, 4);

    page.test1();
    page.test2();
}
