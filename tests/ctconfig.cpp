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
 * @file ctconfig.cpp
 * @brief 
 * @date 06-02-2025
 * 
 */

#include <gtest/gtest.h>
#include "cpptoolkit.hpp"

/**************************** Helper definitions ****************************/
#define CT_CONFIG_FILE      "config.txt"

#define UINT_KEY            "uint.ex"
#define UINT_VALUE          1

#define INT_KEY             "int.ex"
#define INT_VALUE           -10

#define DOUBLE_KEY          "double.ex"
#define DOUBLE_VALUE        9.199999999999999999

#define FLOAT_KEY           "float.ex"
#define FLOAT_VALUE         9.2

#define STRING_KEY          "string.ex"
#define STRING_VALUE        "Hello! This is a string."


/********************************* Main test ********************************/

/**
 * @brief CtConfigTest01
 * 
 * @details
 * Test writing, reading and reseting.
 * 
 */
TEST(CtConfig, CtConfigTest01) {
    {
        CtConfig config(CT_CONFIG_FILE);
        config.writeUInt(UINT_KEY, UINT_VALUE);
        config.writeInt(INT_KEY, INT_VALUE);
        config.writeDouble(DOUBLE_KEY, DOUBLE_VALUE);
        config.writeFloat(FLOAT_KEY, FLOAT_VALUE);
        config.writeString(STRING_KEY, STRING_VALUE);
        config.write();
    }
    {
        CtConfig config(CT_CONFIG_FILE);
        config.read();
        CtUInt32 temp01 = config.parseAsUInt(UINT_KEY);
        CtInt32 temp02 = config.parseAsInt(INT_KEY);
        CtDouble temp03 = config.parseAsDouble(DOUBLE_KEY);
        CtFloat temp04 = config.parseAsFloat(FLOAT_KEY);
        CtString temp05 = config.parseAsString(STRING_KEY);
        ASSERT_EQ(temp01, UINT_VALUE);
        ASSERT_EQ(temp02, INT_VALUE);
        ASSERT_EQ(temp03, DOUBLE_VALUE);
        ASSERT_EQ(temp04, (float)FLOAT_VALUE);
        ASSERT_EQ(temp05, STRING_VALUE);
        config.reset();
        EXPECT_THROW({
            temp01 = config.parseAsUInt(UINT_KEY);
        }, CtKeyNotFoundError);
    }
}

/**
 * @brief CtConfigTest02
 * 
 * @details
 * Test if CtTypeParseError is thrown when trying to parse a key with a different type.
 * 
 */
TEST(CtConfig, CtConfigTest02) {
    {
        CtConfig config(CT_CONFIG_FILE);
        config.writeUInt(UINT_KEY, UINT_VALUE);
        config.writeDouble(DOUBLE_KEY, DOUBLE_VALUE);
        config.writeFloat(FLOAT_KEY, FLOAT_VALUE);
        config.writeInt(INT_KEY, INT_VALUE);
        config.writeString(STRING_KEY, STRING_VALUE);
        config.write();
    }
    {
        CtConfig config(CT_CONFIG_FILE);
        config.read();
        EXPECT_THROW({
            CtUInt32 temp01 = config.parseAsUInt(STRING_KEY);
        }, CtTypeParseError);
        EXPECT_THROW({
            CtInt32 temp02 = config.parseAsInt(STRING_KEY);
        }, CtTypeParseError);
        EXPECT_THROW({
            CtDouble temp03 = config.parseAsDouble(STRING_KEY);
        }, CtTypeParseError);
        EXPECT_THROW({
            CtFloat temp04 = config.parseAsFloat(STRING_KEY);
        }, CtTypeParseError);
        CtString temp05 = config.parseAsString(UINT_KEY);
        ASSERT_EQ(temp05, ToCtString(UINT_VALUE));
    }
}

/**
 * @brief CtConfigTest03
 * 
 * @details
 * Test writing a key with different types and writing a key with the same name.
 * 
 */
TEST(CtConfig, CtConfigTest03) {
    {
        CtConfig config(CT_CONFIG_FILE);
        config.writeUInt(UINT_KEY, UINT_VALUE);
        config.writeUInt(UINT_KEY, INT_VALUE);
        config.write();
    }
    {
        CtConfig config(CT_CONFIG_FILE);
        config.read();
        CtUInt32 temp01 = config.parseAsUInt(UINT_KEY);
        ASSERT_EQ(temp01, (CtUInt32)INT_VALUE);
    }
}
