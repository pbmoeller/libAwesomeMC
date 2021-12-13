#include "nbt/tags/byte_tag.hpp"
#include "nbt/tags/end_tag.hpp"

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
    std::string name = "CopyConstructor";
    char byte = 0x34;

    // Init
    nbt::ByteTag byteTagA(name, byte);
    ASSERT_STREQ(byteTagA.getName().c_str(), name.c_str());
    ASSERT_EQ(byteTagA.getValue(), byte);

    // Test Copy
    nbt::ByteTag byteTagB(byteTagA);
    EXPECT_STREQ(byteTagB.getName().c_str(), byteTagA.getName().c_str());
    EXPECT_EQ(byteTagB.getValue(), byteTagA.getValue());
}

TEST(ByteTag, MoveConstructor)
{
    std::string name = "MoveConstructor";
    char byte = 0x36;

    // Init
    nbt::ByteTag byteTagA(name, byte);
    ASSERT_STREQ(byteTagA.getName().c_str(), name.c_str());
    ASSERT_EQ(byteTagA.getValue(), byte);

    // Test Move
    nbt::ByteTag byteTagB(std::move(byteTagA));
    EXPECT_STREQ(byteTagB.getName().c_str(), byteTagA.getName().c_str());
    EXPECT_EQ(byteTagB.getValue(), byteTagA.getValue());
}

TEST(ByteTag, CopyAssignment)
{
    std::string name = "CopyAssignment";
    char byte = 0x37;

    // Init A
    nbt::ByteTag byteTagA(name, byte);
    ASSERT_STREQ(byteTagA.getName().c_str(), name.c_str());
    ASSERT_EQ(byteTagA.getValue(), byte);

    // Init B
    nbt::ByteTag byteTagB;
    ASSERT_STREQ(byteTagB.getName().c_str(), "");
    ASSERT_EQ(byteTagB.getValue(), 0);

    // Test Copy Assignment
    byteTagB = byteTagA;
    EXPECT_STREQ(byteTagB.getName().c_str(), byteTagA.getName().c_str());
    EXPECT_EQ(byteTagB.getValue(), byteTagA.getValue());
}

TEST(ByteTag, MoveAssignment)
{
    std::string name = "MoveAssignment";
    char byte = 0x38;

    // Init A
    nbt::ByteTag byteTagA(name, byte);
    ASSERT_STREQ(byteTagA.getName().c_str(), name.c_str());
    ASSERT_EQ(byteTagA.getValue(), byte);

    // Init B
    nbt::ByteTag byteTagB;
    ASSERT_STREQ(byteTagB.getName().c_str(), "");
    ASSERT_EQ(byteTagB.getValue(), 0);

    // Test Move Assignment
    byteTagB = std::move(byteTagA);
    EXPECT_STREQ(byteTagB.getName().c_str(), name.c_str());
    EXPECT_EQ(byteTagB.getValue(), byte);
}

TEST(ByteTag, clone)
{
    nbt::ByteTag byteTagA("Test1", 1);

    nbt::ByteTag *byteTagB = (nbt::ByteTag *)byteTagA.clone();
    EXPECT_TRUE(byteTagA == *byteTagB);
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