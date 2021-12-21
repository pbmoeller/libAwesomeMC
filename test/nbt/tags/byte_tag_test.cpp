#include "nbt/tags/byte_tag.hpp"
#include "nbt/tags/end_tag.hpp"

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

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
    char value = 0x34;

    // Init
    nbt::ByteTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Test Copy
    nbt::ByteTag tagB(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_EQ(tagB.getValue(), tagA.getValue());
}

TEST(ByteTag, MoveConstructor)
{
    std::string name = "MoveConstructor";
    char value = 0x36;

    // Init
    nbt::ByteTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Test Move
    nbt::ByteTag tagB(std::move(tagA));
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_EQ(tagB.getValue(), value);
}

TEST(ByteTag, CopyAssignment)
{
    std::string name = "CopyAssignment";
    char value = 0x37;

    // Init A
    nbt::ByteTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Init B
    nbt::ByteTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_EQ(tagB.getValue(), 0);

    // Test Copy Assignment
    tagB = tagA;
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_EQ(tagB.getValue(), tagA.getValue());
}

TEST(ByteTag, MoveAssignment)
{
    std::string name = "MoveAssignment";
    char value = 0x38;

    // Init A
    nbt::ByteTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Init B
    nbt::ByteTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_EQ(tagB.getValue(), 0);

    // Test Move Assignment
    tagB = std::move(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_EQ(tagB.getValue(), value);
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
    const std::vector<unsigned char> testData = {
        0x01, 0x00, 0x08, 0x62, 0x79, 0x74, 0x65, 0x54, 0x65, 0x73, 0x74, 0x7F
    };

    nbt::ByteTag byteTag("byteTest", 127);
    std::vector<unsigned char> data = byteTag.getData(false);

    EXPECT_EQ(data.size(), testData.size());
    EXPECT_THAT(data, ::testing::ElementsAreArray(testData));

    std::vector<unsigned char> data2 = byteTag.getData(true);
    EXPECT_EQ(1, data2.size());
    EXPECT_EQ(127, data2[0]);
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