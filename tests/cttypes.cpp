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
 * @file cttypes.cpp
 * @brief 
 * @date 01-02-2025
 * 
 */

#include <gtest/gtest.h>
#include "cpptoolkit.hpp"

/**************************** Helper definitions ****************************/

/********************************* Main test ********************************/

/**
 * @brief CtRawDataTest01
 * 
 * @details
 * Test the basic functionality of CtRawData class.
 * 
 */
TEST(CtTypes, CtRawDataTest01) {
    CtRawData data;
    data.setNextByte(0x1);
    data.setNextByte(0x2);
    data.setNextByte(0x3);
    ASSERT_EQ(data.size(), 3);
    CtUInt8* buffer = data.get();
    ASSERT_EQ(buffer[0], 0x1);
    ASSERT_EQ(buffer[1], 0x2);
    ASSERT_EQ(buffer[2], 0x3);
    data.reset();
    ASSERT_EQ(data.size(), 0);
}

/**
 * @brief CtRawDataTest02
 * 
 * @details
 * Test if the buffer is correct when setNextByte() is called.
 * 
 */
TEST(CtTypes, CtRawDataTest02) {
    CtRawData data(4);
    data.setNextByte(0x1C);
    data.setNextByte(0x2C);
    CtUInt8 buffer[2] = {0x1C, 0x2C};
    CtUInt8 res = memcmp(data.get(), buffer, data.size());
    ASSERT_EQ(res, 0);
}

/**
 * @brief CtRawDataTest03
 * 
 * @details
 * Test if CtOutOfRangeError is thrown when setNextByte() is called and the buffer is full.
 * 
 */
TEST(CtTypes, CtRawDataTest03) {
    CtRawData data(1);
    data.setNextByte(0x1);
    EXPECT_THROW({
        data.setNextByte(0x2);
    }, CtOutOfRangeError);
}

/**
 * @brief CtRawDataTest04
 * 
 * @details
 * Test if the buffer is correct when setNextBytes() is called.
 * 
 */
TEST(CtTypes, CtRawDataTest04) {
    CtUInt8 buffer[5] = {0x1C};
    CtRawData data(5);
    data.setNextBytes(buffer, 5);
    CtUInt8 res = memcmp(data.get(), buffer, data.size());
    ASSERT_EQ(res, 0);
}

/**
 * @brief CtRawDataTest05
 * 
 * @details
 * Test if CtOutOfRangeError is thrown when setNextBytes() is called and the buffer is full.
 * 
 */
TEST(CtTypes, CtRawDataTest05) {
    CtUInt8 buffer[5] = {0x1C};
    CtRawData data(4);
    EXPECT_THROW({
        data.setNextBytes(buffer, 5);
    }, CtOutOfRangeError);
}

/**
 * @brief CtRawDataTest06
 * 
 * @details
 * Test if the buffer is correct when a CtRawData object is copied.
 * 
 */
TEST(CtTypes, CtRawDataTest06) {
    CtRawData data1(3);
    data1.setNextByte(0x1C);
    data1.setNextByte(0x2C);
    data1.setNextByte(0x3C);
    CtRawData data2(data1);
    CtUInt8 res = memcmp(data1.get(), data2.get(), 3);
    ASSERT_EQ(res, 0);
}

/**
 * @brief CtRawDataTest07
 * 
 * @details
 * Test if getNLastBytes() returns the correct buffer.
 * 
 */
TEST(CtTypes, CtRawDataTest08) {
    CtRawData data(6);
    data.setNextByte(0x1C);
    data.setNextByte(0x2C);
    data.setNextByte(0x3C);
    data.setNextByte(0x4C);
    data.setNextByte(0x5C);
    data.setNextByte(0x6C);
    CtUInt8* buffer1 = data.getNLastBytes(3);
    CtUInt8 buffer2[3] = {0x4C, 0x5C, 0x6C};
    CtUInt8 res = memcmp(buffer1, buffer2, 3);
    ASSERT_EQ(res, 0);
}

/**
 * @brief CtRawDataTest09
 * 
 * @details
 * Test if CtOutOfRangeError is thrown when getNLastBytes() is called and the buffer is not full.
 * 
 */
TEST(CtTypes, CtRawDataTest09) {
    CtRawData data(10);
    data.setNextByte(0x1C);
    data.setNextByte(0x2C);
    data.setNextByte(0x3C);
    data.setNextByte(0x4C);
    data.setNextByte(0x5C);
    data.setNextByte(0x6C);
    EXPECT_THROW({
        data.getNLastBytes(7);
    }, CtOutOfRangeError);
}

/**
 * @brief CtRawDataTest10
 * 
 * @details
 * Test if the buffer is correct when removeNLastBytes() is called.
 * 
 */
TEST(CtTypes, CtRawDataTest10) {
    CtRawData data(10);
    data.setNextByte(0x1C);
    data.setNextByte(0x2C);
    data.setNextByte(0x3C);
    data.setNextByte(0x4C);
    data.setNextByte(0x5C);
    data.setNextByte(0x6C);
    data.removeNLastBytes(2);
    CtUInt8 buffer[4] = {0x1C, 0x2C, 0x3C, 0x4C};
    ASSERT_EQ(data.size(), 4);
    CtUInt8 res = memcmp(data.get(), buffer, 4);
    ASSERT_EQ(res, 0);
}

/**
 * @brief CtRawDataTest11
 * 
 * @details
 * Test if CtOutOfRangeError is thrown when removeNLastBytes() is called and the buffer is not full.
 * 
 */
TEST(CtTypes, CtRawDataTest11) {
    CtRawData data(10);
    data.setNextByte(0x1C);
    data.setNextByte(0x2C);
    data.setNextByte(0x3C);
    data.setNextByte(0x4C);
    data.setNextByte(0x5C);
    data.setNextByte(0x6C);
    EXPECT_THROW({
        data.removeNLastBytes(7);
    }, CtOutOfRangeError);
}

/**
 * @brief CtRawDataTest12
 * 
 * @details
 * Test if the buffer is correct when a CtRawData object is assigned.
 * 
 */
TEST(CtTypes, CtRawDataTest12) {
    CtRawData data1(10);
    data1.setNextByte(0x1C);
    data1.setNextByte(0x2C);
    CtRawData data2 = data1;
    CtUInt8 res = memcmp(data1.get(), data2.get(), data1.size());
    ASSERT_EQ(res, 0);

    data2.setNextByte(0x3C);
    ASSERT_NE(data1.size(), data2.size());
}

/**
 * @brief CtRawDataTest13
 * 
 * @details
 * Test if the buffer is correct when clone() is called.
 * 
 */
TEST(CtTypes, CtRawDataTest13) {
    CtRawData data(2);
    CtUInt8 buffer[2] = {0x1C};
    ASSERT_EQ(data.size(), 0);
    data.clone(buffer, 2);
    ASSERT_EQ(data.size(), 2);
    CtUInt8 res = memcmp(data.get(), buffer, 2);
    ASSERT_EQ(res, 0);
}

/**
 * @brief CtRawDataTest14
 * 
 * @details
 * Test if CtOutOfRangeError is thrown when clone() is called and the buffer is bigger than the CtRawData object.
 * 
 */
TEST(CtTypes, CtRawDataTest14) {
    CtRawData data(1);
    CtUInt8 buffer[2] = {0x1C};
    EXPECT_THROW({
        data.clone(buffer, 2);
    }, CtOutOfRangeError);
}
