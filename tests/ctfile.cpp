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
 * @file ctfile.cpp
 * @brief 
 * @date 02-02-2025
 * 
 */

#include <gtest/gtest.h>
#include "cpptoolkit.hpp"

/**************************** Helper definitions ****************************/

/********************************* Main test ********************************/

/**
 * @brief CtFileIOTest01
 * 
 * @details
 * Test the basic functionality of CtFileInput and CtFileOutput classes.
 * CtFileOutput writes a string to a file and CtFileInput reads it back.
 * CtFileOutput is tested with Truncate mode.
 * The file used is the same for all test cases.
 * 
 */
TEST(CtFileIO, CtFileIOTest01) {
    /* Write data to a file */
    {
        CtRawData data;
        CtFileOutput fileOut("file.txt", CtFileOutput::WriteMode::Truncate);
        fileOut.setDelimiter("\n", 1);

        data.clone((CtUInt8*)"HelloTest01", 11);
        fileOut.write(&data);
    }
    /* Read data of a file */
    {
        CtRawData data;
        CtFileInput fileIn("file.txt");
        fileIn.setDelimiter("\n", 1);

        fileIn.read(&data);
        CtUInt8* buffer = data.get();
        CtUInt8 res = memcmp(buffer, "HelloTest01", 11);
        ASSERT_EQ(res, 0);
    }
}

/**
 * @brief CtFileIOTest02
 * 
 * @details
 * Test the basic functionality of CtFileInput and CtFileOutput classes.
 * CtFileOutput writes a string to a file and CtFileInput reads it back.
 * CtFileOutput is tested with Append mode.
 * The file used is the same for all test cases.
 * 
 */

TEST(CtFileIO, CtFileIOTest02) {
    /* Append data to a file */
    {
        CtRawData data;
        CtFileOutput fileOut("file.txt", CtFileOutput::WriteMode::Append);
        fileOut.setDelimiter("\n", 1);

        data.clone((CtUInt8*)"HelloTest02", 11);
        fileOut.write(&data);
    }
    /* Read data of a file */
    {
        CtRawData data;
        CtFileInput fileIn("file.txt");
        fileIn.setDelimiter("\n", 1);

        CtBool status = fileIn.read(&data);
        CtUInt8* buffer = data.get();
        CtUInt8 res = memcmp(buffer, "HelloTest01", 11);
        ASSERT_EQ(res, 0);
        ASSERT_EQ(status, CT_TRUE);

        status = fileIn.read(&data);
        buffer = data.get();
        res = memcmp(buffer, "HelloTest02", 11);
        ASSERT_EQ(res, 0);
        ASSERT_EQ(status, CT_TRUE);

        status = fileIn.read(&data);
        ASSERT_EQ(status, CT_FALSE);
    }
}

/**
 * @brief CtFileIOTest03
 * 
 * @details
 * Test CtFileOutput throw CtFileReadError when file does not exists.
 * 
 */

TEST(CtFileIO, CtFileIOTest03) {
    /* Read a file that does not exists */
    EXPECT_THROW({
        CtFileInput fileIn("file2.txt");
    }, CtFileReadError);
}

/**
 * @brief CtFileIOTest04
 * 
 * @details
 * Test reading from an empty file.
 * 
 */
TEST(CtFileIO, CtFileIOTest04) {
    /* Create an empty file */
    {
        CtFileOutput fileOut("empty.txt", CtFileOutput::WriteMode::Truncate);
        fileOut.setDelimiter("\n", 1);
    }
    /* Read the empty file */
    {
        CtRawData data;
        CtFileInput fileIn("empty.txt");
        fileIn.setDelimiter("\n", 1);

        CtBool status = fileIn.read(&data);
        ASSERT_EQ(status, CT_FALSE);
    }
}

/**
 * @brief CtFileIOTest05
 * 
 * @details
 * Test handling file larger than the buffer with no delimiter using write.
 * 
 */
TEST(CtFileIO, CtFileIOTest05) {
    CtString largeString(10000, 0x1C);
    /* Write largeString to large.txt two times with no delimeters */
    {
        CtRawData data(10000);
        CtFileOutput fileOut("large.txt", CtFileOutput::WriteMode::Truncate);
        fileOut.setDelimiter("", 0);

        data.clone((CtUInt8*)largeString.c_str(), largeString.size());
        fileOut.write(&data);
        fileOut.write(&data);
    }
    /* Read data in a 1000 bytes buffer */
    {
        CtRawData data(1000);
        CtFileInput fileIn("large.txt");
        fileIn.setDelimiter("\n", 1);

        fileIn.read(&data);
        ASSERT_EQ(data.size(), 999);
    }
    /* Read data in a 100000 bytes buffer */
    {
        CtRawData data(100000);
        CtFileInput fileIn("large.txt");
        fileIn.setDelimiter("\n", 1);

        fileIn.read(&data);
        ASSERT_EQ(data.size(), 20000);
    }
}

/**
 * @brief CtFileIOTest06
 * 
 * @details
 * Test handling file larger than the buffer with no delimiter using writePart.
 * 
 */
TEST(CtFileIO, CtFileIOTest06) {
    CtString largeString(10000, 0x1C);
    /* Write largeString to large.txt two times with no delimeters */
    {
        CtRawData data(10000);
        CtFileOutput fileOut("large.txt", CtFileOutput::WriteMode::Truncate);

        data.clone((CtUInt8*)largeString.c_str(), largeString.size());
        fileOut.writePart(&data);
        fileOut.writePart(&data);
    }
    /* Read data in a 1000 bytes buffer */
    {
        CtRawData data(1000);
        CtFileInput fileIn("large.txt");
        fileIn.setDelimiter("\n", 1);

        fileIn.read(&data);
        ASSERT_EQ(data.size(), 999);
    }
    /* Read data in a 100000 bytes buffer */
    {
        CtRawData data(100000);
        CtFileInput fileIn("large.txt");
        fileIn.setDelimiter("\n", 1);

        fileIn.read(&data);
        ASSERT_EQ(data.size(), 20000);
    }
}

/**
 * @brief CtFileIOTest07
 * 
 * @details
 * Test handling file larger than the buffer with delimiters.
 * 
 */
TEST(CtFileIO, CtFileIOTest07) {
    CtString largeString(10000, 0x1C);
    /* Write largeString to large.txt two times with delimeters */
    {
        CtRawData data(10000);
        CtFileOutput fileOut("large.txt", CtFileOutput::WriteMode::Truncate);
        fileOut.setDelimiter("\n", 1);

        data.clone((CtUInt8*)largeString.c_str(), largeString.size());
        fileOut.write(&data);
        fileOut.write(&data);
    }
    /* Read data in a 1000 bytes buffer */
    {
        CtRawData data(1000);
        CtFileInput fileIn("large.txt");
        fileIn.setDelimiter("\n", 1);

        fileIn.read(&data);
        ASSERT_EQ(data.size(), 999);
    }
    /* Read data in a 100000 bytes buffer */
    {
        CtRawData data(100000);
        CtFileInput fileIn("large.txt");
        fileIn.setDelimiter("\n", 1);

        fileIn.read(&data);
        ASSERT_EQ(data.size(), 10000);
        fileIn.read(&data);
        ASSERT_EQ(data.size(), 10000);
        CtBool res = fileIn.read(&data);
        ASSERT_EQ(res, CT_FALSE);
    }
}

/**
 * @brief CtFileIOTest08
 * 
 * @details
 * Test handling files.
 * 
 */
TEST(CtFileIO, CtFileIOTest08) {
    CtString largeString(10000, 0x1C);
    /* Write largeString to large.txt two times with delimeters */
    {
        CtRawData data(10000);
        CtFileOutput fileOut("large.txt", CtFileOutput::WriteMode::Truncate);
        fileOut.setDelimiter("\n", 1);

        data.clone((CtUInt8*)largeString.c_str(), largeString.size());
        fileOut.write(&data);
        fileOut.write(&data);
    }
    /* Read data in a 1000 bytes buffer */
    {
        CtRawData data(1000);
        CtFileInput fileIn("large.txt");
        fileIn.setDelimiter("\n", 1);

        fileIn.read(&data);
        ASSERT_EQ(data.size(), 999);
    }
    /* Read data in a 100000 bytes buffer */
    {
        CtRawData data(100000);
        CtFileInput fileIn("large.txt");
        fileIn.setDelimiter("\n", 1);

        fileIn.read(&data);
        ASSERT_EQ(data.size(), 10000);
        fileIn.read(&data);
        ASSERT_EQ(data.size(), 10000);
        CtBool res = fileIn.read(&data);
        ASSERT_EQ(res, CT_FALSE);
    }
}
