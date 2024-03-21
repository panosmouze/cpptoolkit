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
 * @file CtEvents.hpp
 * @brief 
 * @date 07-03-2024
 * 
 */

#ifndef INCLUDE_CTEVENTS_HPP_
#define INCLUDE_CTEVENTS_HPP_

#define CTEVENT_NO_EVENT                                0
#define CTEVENT_EOF                                     1
#define CTEVENT_DATA_IN                                 2
#define CTEVENT_DATA_OUT                                3
#define CTEVENT_DATA_READY                              4

#define CTEVENT_DATA_IN_FAIL                            111
#define CTEVENT_DATA_OUT_FAIL                           112
#define CTEVENT_DATA_DROP                               113

#endif //INCLUDE_CTEVENTS_HPP_