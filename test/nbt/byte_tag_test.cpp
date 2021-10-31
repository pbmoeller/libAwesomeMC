#include "nbt/byte_tag.hpp"
#include "nbt/end_tag.hpp"

// gtest
#include <gtest/gtest.h>

TEST(ByteTag, Constructor)
{
    nbt::ByteTag byteTag;
    EXPECT_STREQ("", byteTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Byte, byteTag.getType());
    EXPECT_EQ(0, byteTag.getValue());
}

TEST(ByteTag, Constructor_2)
{
    nbt::ByteTag byteTag("TagName");
    EXPECT_STREQ("TagName", byteTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Byte, byteTag.getType());
    EXPECT_EQ(0, byteTag.getValue());
}

TEST(ByteTag, Constructor_3)
{
    char value = 123;
    nbt::ByteTag byteTag(value);
    EXPECT_STREQ("", byteTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Byte, byteTag.getType());
    EXPECT_EQ(value, byteTag.getValue());
}

TEST(ByteTag, Constructor_4)
{
    char value = -5;
    nbt::ByteTag byteTag("TagName", value);
    EXPECT_STREQ("TagName", byteTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Byte, byteTag.getType());
    EXPECT_EQ(value, byteTag.getValue());
}

TEST(ByteTag, CopyConstructor)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ByteTag, MoveConstructor)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ByteTag, CopyAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ByteTag, MoveAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ByteTag, Equal)
{
    nbt::ByteTag byteTagA("Test1", 1);
    nbt::ByteTag byteTagB("Test1", 1);
    nbt::ByteTag byteTagC("Test1", 1);
    nbt::ByteTag byteTagD("Test2", 2);
    nbt::ByteTag byteTagE;
    nbt::EndTag endTag;

    EXPECT_TRUE(byteTagA == byteTagA);  // Test same object
    EXPECT_TRUE(byteTagA == byteTagB);  // Test same data #1
    EXPECT_TRUE(byteTagA == byteTagC);  // Test same data #2
    byteTagB.setValue(3);
    EXPECT_FALSE(byteTagA == byteTagB); // Test different data #1
    byteTagC.setName("Test3");
    EXPECT_FALSE(byteTagA == byteTagC); // Test different data #2

    EXPECT_FALSE(byteTagE == endTag);   // Test different types
}

TEST(ByteTag, NotEqual)
{
    nbt::ByteTag byteTagA("Test1", 1);
    nbt::ByteTag byteTagB("Test1", 1);
    nbt::ByteTag byteTagC("Test1", 1);
    nbt::ByteTag byteTagD("Test2", 2);
    nbt::ByteTag byteTagE;
    nbt::EndTag endTag;

    EXPECT_FALSE(byteTagA != byteTagA);  // Test same object
    EXPECT_FALSE(byteTagA != byteTagB);  // Test same data #1
    EXPECT_FALSE(byteTagA != byteTagC);  // Test same data #2
    byteTagB.setValue(3);
    EXPECT_TRUE(byteTagA != byteTagB); // Test different data #1
    byteTagC.setName("Test3");
    EXPECT_TRUE(byteTagA != byteTagC); // Test different data #2

    EXPECT_TRUE(byteTagE != endTag);   // Test different types
}

TEST(ByteTag, getType)
{
    nbt::ByteTag byteTag;
    EXPECT_EQ(nbt::TagType::Byte, byteTag.getType());
}

TEST(ByteTag, getData)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ByteTag, getValue)
{
    char value = 123;
    char value2 = -128;
    nbt::ByteTag byteTag;
    EXPECT_EQ(0, byteTag.getValue());
    byteTag.setValue(value);
    EXPECT_EQ(value, byteTag.getValue());
    byteTag.setValue(value2);
    EXPECT_EQ(value2, byteTag.getValue());
}

TEST(ByteTag, setValue)
{
    char value = 123;
    char value2 = -128;
    nbt::ByteTag byteTag;
    EXPECT_EQ(0, byteTag.getValue());
    byteTag.setValue(value);
    EXPECT_EQ(value, byteTag.getValue());
    byteTag.setValue(value2);
    EXPECT_EQ(value2, byteTag.getValue());
}