#include "nbt/end_tag.hpp"
#include "nbt/byte_tag.hpp"

// gtest
#include <gtest/gtest.h>

TEST(EndTag, Constructor)
{
    nbt::EndTag endTag;

    EXPECT_EQ(nbt::TagType::End, endTag.getType());
    EXPECT_STREQ("", endTag.getName().c_str());
}

TEST(EndTag, CopyConstructor)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(EndTag, MoveConstructor)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(EndTag, CopyAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(EndTag, MoveAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(EndTag, Equal)
{
    nbt::EndTag byteTagA;
    nbt::EndTag byteTagB;
    nbt::EndTag byteTagC;
    nbt::EndTag byteTagD;
    nbt::ByteTag byteTagE;
    nbt::EndTag endTag;

    EXPECT_TRUE(byteTagA == byteTagA);  // Test same object
    EXPECT_TRUE(byteTagA == byteTagB);  // Test same data #1
    EXPECT_TRUE(byteTagA == byteTagC);  // Test same data #2
    byteTagC.setName("Test3");
    EXPECT_FALSE(byteTagA == byteTagC); // Test different data #2

    EXPECT_FALSE(byteTagE == endTag);   // Test different types
}

TEST(EndTag, NotEqual)
{
    nbt::EndTag byteTagA;
    nbt::EndTag byteTagB;
    nbt::EndTag byteTagC;
    nbt::EndTag byteTagD;
    nbt::ByteTag byteTagE;
    nbt::EndTag endTag;

    EXPECT_FALSE(byteTagA != byteTagA);  // Test same object
    EXPECT_FALSE(byteTagA != byteTagB);  // Test same data #1
    EXPECT_FALSE(byteTagA != byteTagC);  // Test same data #2
    byteTagC.setName("Test3");
    EXPECT_TRUE(byteTagA != byteTagC); // Test different data #2

    EXPECT_TRUE(byteTagE != endTag);   // Test different types
}

TEST(EndTag, getType)
{
    nbt::EndTag byteTag;
    EXPECT_EQ(nbt::TagType::End, byteTag.getType());
}

TEST(EndTag, getData)
{
    nbt::EndTag endTag;

    std::vector<unsigned char> data1 = endTag.getData(true);
    EXPECT_EQ(1, data1.size());
    EXPECT_EQ(0, data1[0]);

    std::vector<unsigned char> data2 = endTag.getData(false);
    EXPECT_EQ(1, data2.size());
    EXPECT_EQ(0, data2[0]);
}

