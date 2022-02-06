// AwesomeMC
#include <AwesomeMC/nbt/tags/byte_tag.hpp>
#include <AwesomeMC/nbt/tags/end_tag.hpp>
#include <AwesomeMC/nbt/tags/int_tag.hpp>

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(ByteTag, Constructor)
{
    amc::ByteTag byteTag;
    EXPECT_STREQ("", byteTag.getName().c_str());
    EXPECT_EQ(amc::TagType::Byte, byteTag.getType());
    EXPECT_EQ(0, byteTag.getValue());
}

TEST(ByteTag, Constructor_2)
{
    amc::ByteTag byteTag("TagName");
    EXPECT_STREQ("TagName", byteTag.getName().c_str());
    EXPECT_EQ(amc::TagType::Byte, byteTag.getType());
    EXPECT_EQ(0, byteTag.getValue());
}

TEST(ByteTag, Constructor_3)
{
    int8_t value = 123;
    amc::ByteTag byteTag(value);
    EXPECT_STREQ("", byteTag.getName().c_str());
    EXPECT_EQ(amc::TagType::Byte, byteTag.getType());
    EXPECT_EQ(value, byteTag.getValue());
}

TEST(ByteTag, Constructor_4)
{
    int8_t value = -5;
    amc::ByteTag byteTag("TagName", value);
    EXPECT_STREQ("TagName", byteTag.getName().c_str());
    EXPECT_EQ(amc::TagType::Byte, byteTag.getType());
    EXPECT_EQ(value, byteTag.getValue());
}

TEST(ByteTag, CopyConstructor)
{
    std::string name = "CopyConstructor";
    int8_t value = 0x34;

    // Init
    amc::ByteTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Test Copy
    amc::ByteTag tagB(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_EQ(tagB.getValue(), tagA.getValue());
}

TEST(ByteTag, MoveConstructor)
{
    std::string name = "MoveConstructor";
    int8_t value = 0x36;

    // Init
    amc::ByteTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Test Move
    amc::ByteTag tagB(std::move(tagA));
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_EQ(tagB.getValue(), value);
}

TEST(ByteTag, CopyAssignment)
{
    std::string name = "CopyAssignment";
    int8_t value = 0x37;

    // Init A
    amc::ByteTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Init B
    amc::ByteTag tagB;
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
    int8_t value = 0x38;

    // Init A
    amc::ByteTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Init B
    amc::ByteTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_EQ(tagB.getValue(), 0);

    // Test Move Assignment
    tagB = std::move(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_EQ(tagB.getValue(), value);
}

TEST(ByteTag, clone)
{
    amc::ByteTag byteTagA("Test1", 1);

    amc::ByteTag *byteTagB = tag_cast<amc::ByteTag*>(byteTagA.clone());
    EXPECT_TRUE(byteTagA == *byteTagB);

    delete byteTagB;
}

TEST(ByteTag, Equal)
{
    amc::ByteTag byteTagA("Test1", 1);
    amc::ByteTag byteTagB("Test1", 1);
    amc::ByteTag byteTagC("Test1", 1);
    amc::ByteTag byteTagD("Test2", 2);
    amc::ByteTag byteTagE;
    amc::EndTag endTag;

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
    amc::ByteTag byteTagA("Test1", 1);
    amc::ByteTag byteTagB("Test1", 1);
    amc::ByteTag byteTagC("Test1", 1);
    amc::ByteTag byteTagD("Test2", 2);
    amc::ByteTag byteTagE;
    amc::EndTag endTag;

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
    amc::ByteTag byteTag;
    EXPECT_EQ(amc::TagType::Byte, byteTag.getType());
}

TEST(ByteTag, getData)
{
    const std::vector<unsigned char> testData = {
        0x01, 0x00, 0x08, 0x62, 0x79, 0x74, 0x65, 0x54, 0x65, 0x73, 0x74, 0x7F
    };

    amc::ByteTag byteTag("byteTest", 127);
    std::vector<unsigned char> data = byteTag.getData(false);

    EXPECT_EQ(data.size(), testData.size());
    EXPECT_THAT(data, ::testing::ElementsAreArray(testData));

    std::vector<unsigned char> data2 = byteTag.getData(true);
    EXPECT_EQ(1, data2.size());
    EXPECT_EQ(127, data2[0]);
}

TEST(ByteTag, getValue)
{
    int8_t value = 123;
    int8_t value2 = -128;
    amc::ByteTag byteTag;
    EXPECT_EQ(0, byteTag.getValue());
    byteTag.setValue(value);
    EXPECT_EQ(value, byteTag.getValue());
    byteTag.setValue(value2);
    EXPECT_EQ(value2, byteTag.getValue());
}

TEST(ByteTag, setValue)
{
    int8_t value = 123;
    int8_t value2 = -128;
    amc::ByteTag byteTag;
    EXPECT_EQ(0, byteTag.getValue());
    byteTag.setValue(value);
    EXPECT_EQ(value, byteTag.getValue());
    byteTag.setValue(value2);
    EXPECT_EQ(value2, byteTag.getValue());
}

TEST(ByteTag, tag_cast)
{
    amc::AbstractTag *testTag = new amc::ByteTag("A", 2);

    amc::ByteTag *otherTag = tag_cast<amc::ByteTag*>(testTag);
    EXPECT_EQ(otherTag, testTag);

    amc::IntTag *nullTag = tag_cast<amc::IntTag*>(testTag);
    EXPECT_EQ(nullTag, nullptr);

    delete testTag;
}