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
 * @file ex05_config.cpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#include "CtIO.hpp"

#include <iostream>

int main() {
    CtConfigParser parser("config.ini");
    parser.read();
    std::cout << parser.parseAsUInt("alpha") << std::endl;
    std::cout << parser.parseAsInt("beta") << std::endl;
    std::cout << parser.parseAsFloat("gamma") << std::endl;
    std::cout << parser.parseAsString("name") << std::endl;
    std::cout << parser.parseAsString("email") << std::endl;
    parser.writeDouble("float_example", 1.1111111111111112);
    parser.writeInt("int_example", -1);
    parser.writeUInt("uint_example", 2);
    parser.writeString("string_example", "2F");
    parser.write();
    return 0;
}
