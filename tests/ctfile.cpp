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
#define CT_FILENAME         "test.txt"
#define CT_DEL              "\n"
#define CT_NO_DEL           ""

/********************************* Main test ********************************/

/**
 * @brief CtFileIOTest01
 * 
 * @details
 * Test the basic functionality of CtFileInput and CtFileOutput classes.
 * CtFileOutput writes a string to a file and CtFileInput reads it back.
 * CtFileOutput is tested with Truncate mode.
 * 
 * @ref FR-002-002-001
 * @ref FR-002-002-002
 * @ref FR-002-002-003
 * @ref FR-002-002-006
 * @ref FR-002-001-007
 * 
 */
TEST(CtFileIO, CtFileIOTest01) {
    int status = system("rm -f test.txt");
    ASSERT_NE(status, -1);
    /* Write data to a file */
    {
        CtRawData data;
        CtFileOutput fileOut(CT_FILENAME, CtFileOutput::WriteMode::Truncate);
        fileOut.setDelimiter(CT_DEL, sizeof(CT_DEL));

        data.clone((CtUInt8*)"HelloTest01", 11);
        fileOut.write(&data);
    }
    /* Read data of a file */
    {
        CtRawData data;
        CtFileInput fileIn(CT_FILENAME);
        fileIn.setDelimiter(CT_DEL, sizeof(CT_DEL));

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
 * 
 * @ref FR-002-002-001
 * @ref FR-002-002-002
 * @ref FR-002-002-003
 * @ref FR-002-002-005
 * @ref FR-002-002-006
 * @ref FR-002-002-007
 * 
 * @ref FR-002-001-001
 * @ref FR-002-001-002
 * @ref FR-002-001-004
 * @ref FR-002-001-005
 * @ref FR-002-001-006
 * @ref FR-002-001-007
 * @ref FR-002-001-009
 * @ref FR-002-001-010
 * 
 */

TEST(CtFileIO, CtFileIOTest02) {
    int status = system("rm -f test.txt");
    ASSERT_NE(status, -1);
    /* Append data to a file */
    {
        CtRawData data;
        CtFileOutput fileOut(CT_FILENAME, CtFileOutput::WriteMode::Append);
        fileOut.setDelimiter(CT_DEL, sizeof(CT_DEL));

        data.clone((CtUInt8*)"HelloTest01", 11);
        fileOut.write(&data);
    }
    {
        CtRawData data;
        CtFileOutput fileOut(CT_FILENAME, CtFileOutput::WriteMode::Append);
        fileOut.setDelimiter(CT_DEL, sizeof(CT_DEL));

        data.clone((CtUInt8*)"HelloTest02", 11);
        fileOut.write(&data);
    }
    /* Read data of a file */
    {
        CtRawData data;
        CtFileInput fileIn(CT_FILENAME);
        fileIn.setDelimiter(CT_DEL, sizeof(CT_DEL));

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
 * Test CtFileInput throw CtFileReadError when file does not exists.
 * 
 * @ref FR-002-001-003
 * 
 */

TEST(CtFileIO, CtFileIOTest03) {
    int status = system("rm -f test.txt");
    ASSERT_NE(status, -1);
    /* Read a file that does not exists */
    EXPECT_THROW({
        CtFileInput fileIn(CT_FILENAME);
    }, CtFileReadError);
}

/**
 * @brief CtFileIOTest04
 * 
 * @details
 * Test CtFileOutput throw CtFileWriteError when file cannot be written.
 * 
 * @ref FR-002-002-004
 * 
 */

TEST(CtFileIO, CtFileIOTest04) {
    int status = system("rm -f test.txt");
    ASSERT_NE(status, -1);
    status = system("touch test.txt");
    ASSERT_NE(status, -1);
    status = system("chmod -w test.txt");
    ASSERT_NE(status, -1);
    EXPECT_THROW({
        CtFileOutput fileOut(CT_FILENAME);
    }, CtFileWriteError);
}

/**
 * @brief CtFileIOTest05
 * 
 * @details
 * Test reading from an empty file.
 * 
 */
TEST(CtFileIO, CtFileIOTest05) {
    int status = system("rm -f test.txt");
    ASSERT_NE(status, -1);
    status = system("touch test.txt");
    ASSERT_NE(status, -1);
    {
        CtRawData data;
        CtFileInput fileIn(CT_FILENAME);
        fileIn.setDelimiter(CT_DEL, sizeof(CT_DEL));

        CtBool status = fileIn.read(&data);
        ASSERT_EQ(status, CT_FALSE);
    }
}

/**
 * @brief CtFileIOTest06
 * 
 * @details
 * Test handling file larger than the buffer with no delimiter using write.
 * 
 * @ref FR-002-002-007
 * @ref FR-002-002-008
 * @ref FR-002-001-008
 * 
 */
TEST(CtFileIO, CtFileIOTest06) {
    int status = system("rm -f test.txt");
    ASSERT_NE(status, -1);
    CtString largeString(10000, 0x1C);
    {
        CtRawData data(10000);
        CtFileOutput fileOut(CT_FILENAME, CtFileOutput::WriteMode::Truncate);
        fileOut.setDelimiter(nullptr, 0);

        data.clone((CtUInt8*)largeString.c_str(), largeString.size());
        fileOut.write(&data);
        fileOut.write(&data);
    }
    {
        CtRawData data(1000);
        CtFileInput fileIn(CT_FILENAME);
        fileIn.setDelimiter(nullptr, 0);

        fileIn.read(&data);
        ASSERT_EQ(data.size(), 1000);
    }
    {
        CtRawData data(1000);
        CtFileInput fileIn(CT_FILENAME);
        fileIn.setDelimiter(CT_DEL, sizeof(CT_DEL));

        for (CtInt8 i = 0; i < 20; i++) {
            fileIn.read(&data);
            ASSERT_EQ(data.size(), 998);
        }
        fileIn.read(&data);
        ASSERT_EQ(data.size(), 40);
    }
    {
        CtRawData data(100000);
        CtFileInput fileIn(CT_FILENAME);
        fileIn.setDelimiter(nullptr, 0);

        fileIn.read(&data);
        ASSERT_EQ(data.size(), 20000);
    }
}

/**
 * @brief CtFileIOTest07
 * 
 * @details
 * Test handling file larger than the buffer with no delimiter using writePart.
 * 
 * @ref FR-002-002-009
 * @ref FR-002-001-008
 * 
 */
TEST(CtFileIO, CtFileIOTest07) {
    int status = system("rm -f test.txt");
    ASSERT_NE(status, -1);
    CtString largeString(10000, 0x1C);
    {
        CtRawData data(10000);
        CtFileOutput fileOut(CT_FILENAME, CtFileOutput::WriteMode::Truncate);
        fileOut.setDelimiter(CT_DEL, sizeof(CT_DEL));

        data.clone((CtUInt8*)largeString.c_str(), largeString.size());
        fileOut.writePart(&data);
        fileOut.writePart(&data);
    }
    {
        CtRawData data(1000);
        CtFileInput fileIn(CT_FILENAME);
        fileIn.setDelimiter(nullptr, 0);

        fileIn.read(&data);
        ASSERT_EQ(data.size(), 1000);
    }
    {
        CtRawData data(1000);
        CtFileInput fileIn(CT_FILENAME);
        fileIn.setDelimiter(CT_DEL, sizeof(CT_DEL));

        for (CtInt8 i = 0; i < 20; i++) {
            fileIn.read(&data);
            ASSERT_EQ(data.size(), 998);
        }
        fileIn.read(&data);
        ASSERT_EQ(data.size(), 40);
    }
    {
        CtRawData data(100000);
        CtFileInput fileIn(CT_FILENAME);
        fileIn.setDelimiter(nullptr, 0);

        fileIn.read(&data);
        ASSERT_EQ(data.size(), 20000);
    }
}
