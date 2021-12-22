#include "nbt/tags/int_tag.hpp"
#include "nbt/tags/byte_tag.hpp"
#include "nbt/tags/end_tag.hpp"

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(IntTag, Constructor)
{
    nbt::IntTag intTag;
    EXPECT_STREQ("", intTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Int, intTag.getType());
    EXPECT_EQ(0, intTag.getValue());
}

TEST(IntTag, Constructor_2)
{
    nbt::IntTag intTag("TagName");
    EXPECT_STREQ("TagName", intTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Int, intTag.getType());
    EXPECT_EQ(0, intTag.getValue());
}

TEST(IntTag, Constructor_3)
{
    int32_t value = 0x012345678;
    nbt::IntTag intTag(value);
    EXPECT_STREQ("", intTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Int, intTag.getType());
    EXPECT_EQ(value, intTag.getValue());
}

TEST(IntTag, Constructor_4)
{
    int32_t value = 0x81234567;
    nbt::IntTag intTag("TagName", value);
    EXPECT_STREQ("TagName", intTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Int, intTag.getType());
    EXPECT_EQ(value, intTag.getValue());
}

TEST(IntTag, CopyConstructor)
{
    std::string name = "CopyConstructor";
    uint32_t value = 0x12345678;

    // Init
    nbt::IntTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Test Copy
    nbt::IntTag tagB(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_EQ(tagB.getValue(), tagA.getValue());
}

TEST(IntTag, MoveConstructor)
{
    std::string name = "MoveConstructor";
    uint32_t value = 0x12345679;

    // Init
    nbt::IntTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Test Move
    nbt::IntTag tagB(std::move(tagA));
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_EQ(tagB.getValue(), value);
}

TEST(IntTag, CopyAssignment)
{
    std::string name = "CopyAssignment";
    uint32_t value = 0x1234567A;

    // Init A
    nbt::IntTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Init B
    nbt::IntTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_EQ(tagB.getValue(), 0);

    // Test Copy Assignment
    tagB = tagA;
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_EQ(tagB.getValue(), tagA.getValue());
}

TEST(IntTag, MoveAssignment)
{
    std::string name = "MoveAssignment";
    uint32_t value = 0x1234567B;

    // Init A
    nbt::IntTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Init B
    nbt::IntTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_EQ(tagB.getValue(), 0);

    // Test Move Assignment
    tagB = std::move(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_EQ(tagB.getValue(), value);
}

TEST(IntTag, clone)
{
    nbt::IntTag intTagA("Test1", 0x81234567);

    nbt::IntTag *intTagB = tag_cast<nbt::IntTag*>(intTagA.clone());
    EXPECT_TRUE(intTagA == *intTagB);
}

TEST(IntTag, Equal)
{
    nbt::IntTag intTagA("Test1", 0x81234567);
    nbt::IntTag intTagB("Test1", 0x81234567);
    nbt::IntTag intTagC("Test1", 0x81234567);
    nbt::IntTag intTagD("Test2", 2);
    nbt::IntTag intTagE;
    nbt::EndTag endTag;

    EXPECT_TRUE(intTagA == intTagA);  // Test same object
    EXPECT_TRUE(intTagA == intTagB);  // Test same data #1
    EXPECT_TRUE(intTagA == intTagC);  // Test same data #2
    intTagB.setValue(3);
    EXPECT_FALSE(intTagA == intTagB); // Test different data #1
    intTagC.setName("Test3");
    EXPECT_FALSE(intTagA == intTagC); // Test different data #2

    EXPECT_FALSE(intTagE == endTag);   // Test different types
}

TEST(IntTag, NotEqual)
{
    nbt::IntTag intTagA("Test1", 0x01234567);
    nbt::IntTag intTagB("Test1", 0x01234567);
    nbt::IntTag intTagC("Test1", 0x01234567);
    nbt::IntTag intTagD("Test2", 2);
    nbt::IntTag intTagE;
    nbt::EndTag endTag;

    EXPECT_FALSE(intTagA != intTagA);  // Test same object
    EXPECT_FALSE(intTagA != intTagB);  // Test same data #1
    EXPECT_FALSE(intTagA != intTagC);  // Test same data #2
    intTagB.setValue(3);
    EXPECT_TRUE(intTagA != intTagB); // Test different data #1
    intTagC.setName("Test3");
    EXPECT_TRUE(intTagA != intTagC); // Test different data #2

    EXPECT_TRUE(intTagE != endTag);   // Test different types
}

TEST(IntTag, getType)
{
    nbt::IntTag intTag;
    EXPECT_EQ(nbt::TagType::Int, intTag.getType());
}

TEST(IntTag, getData)
{
    const std::vector<unsigned char> testData = {
        0x03, 0x00, 0x07, 0x69, 0x6E, 0x74, 0x54, 0x65,
        0x73, 0x74, 0x7F, 0xFF, 0xFF, 0xFF
    };

    nbt::IntTag intTag("intTest", 2147483647);
    std::vector<unsigned char> data = intTag.getData(false);

    EXPECT_EQ(data.size(), testData.size());
    EXPECT_THAT(data, ::testing::ElementsAreArray(testData));

    std::vector<unsigned char> data2 = intTag.getData(true);
    EXPECT_EQ(4, data2.size());
    EXPECT_THAT(data2, ::testing::ElementsAreArray(testData.begin() + 10, testData.end()));
}

TEST(IntTag, getValue)
{
    int32_t value = 12390;
    int32_t value2 = -12878;
    nbt::IntTag intTag;
    EXPECT_EQ(0, intTag.getValue());
    intTag.setValue(value);
    EXPECT_EQ(value, intTag.getValue());
    intTag.setValue(value2);
    EXPECT_EQ(value2, intTag.getValue());
}

TEST(IntTag, setValue)
{
    int32_t value = 12311;
    int32_t value2 = -12834;
    nbt::IntTag intTag;
    EXPECT_EQ(0, intTag.getValue());
    intTag.setValue(value);
    EXPECT_EQ(value, intTag.getValue());
    intTag.setValue(value2);
    EXPECT_EQ(value2, intTag.getValue());
}

TEST(IntTag, tag_cast)
{
    nbt::AbstractTag *testTag = new nbt::IntTag("A", 2);

    nbt::IntTag *otherTag = tag_cast<nbt::IntTag*>(testTag);
    EXPECT_EQ(otherTag, testTag);

    nbt::ByteTag *nullTag = tag_cast<nbt::ByteTag*>(testTag);
    EXPECT_EQ(nullTag, nullptr);
}