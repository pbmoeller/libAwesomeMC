#include "nbt/tags/short_tag.hpp"
#include "nbt/tags/end_tag.hpp"
#include "nbt/tags/int_tag.hpp"

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(ShortTag, Constructor)
{
    nbt::ShortTag shortTag;
    EXPECT_STREQ("", shortTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Short, shortTag.getType());
    EXPECT_EQ(0, shortTag.getValue());
}

TEST(ShortTag, Constructor_2)
{
    nbt::ShortTag shortTag("TagName");
    EXPECT_STREQ("TagName", shortTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Short, shortTag.getType());
    EXPECT_EQ(0, shortTag.getValue());
}

TEST(ShortTag, Constructor_3)
{
    int16_t value = 12345;
    nbt::ShortTag shortTag(value);
    EXPECT_STREQ("", shortTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Short, shortTag.getType());
    EXPECT_EQ(value, shortTag.getValue());
}

TEST(ShortTag, Constructor_4)
{
    int16_t value = -5001;
    nbt::ShortTag shortTag("TagName", value);
    EXPECT_STREQ("TagName", shortTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Short, shortTag.getType());
    EXPECT_EQ(value, shortTag.getValue());
}

TEST(ShortTag, CopyConstructor)
{
    std::string name = "CopyConstructor";
    uint16_t value = 0x1234;

    // Init
    nbt::ShortTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Test Copy
    nbt::ShortTag tagB(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_EQ(tagB.getValue(), tagA.getValue());
}

TEST(ShortTag, MoveConstructor)
{
    std::string name = "MoveConstructor";
    uint16_t value = 0x1235;

    // Init
    nbt::ShortTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Test Move
    nbt::ShortTag tagB(std::move(tagA));
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_EQ(tagB.getValue(), value);
}

TEST(ShortTag, CopyAssignment)
{
    std::string name = "CopyAssignment";
    uint16_t value = 0x1237;

    // Init A
    nbt::ShortTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Init B
    nbt::ShortTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_EQ(tagB.getValue(), 0);

    // Test Copy Assignment
    tagB = tagA;
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_EQ(tagB.getValue(), tagA.getValue());
}

TEST(ShortTag, MoveAssignment)
{
    std::string name = "MoveAssignment";
    uint16_t value = 0x1238;

    // Init A
    nbt::ShortTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Init B
    nbt::ShortTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_EQ(tagB.getValue(), 0);

    // Test Move Assignment
    tagB = std::move(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_EQ(tagB.getValue(), value);
}

TEST(ShortTag, clone)
{
    nbt::ShortTag shortTagA("Test1", 1);

    nbt::ShortTag *shortTagB = tag_cast<nbt::ShortTag*>(shortTagA.clone());
    EXPECT_TRUE(shortTagA == *shortTagB);
}

TEST(ShortTag, Equal)
{
    nbt::ShortTag shortTagA("Test1", 1);
    nbt::ShortTag shortTagB("Test1", 1);
    nbt::ShortTag shortTagC("Test1", 1);
    nbt::ShortTag shortTagD("Test2", 2);
    nbt::ShortTag shortTagE;
    nbt::EndTag endTag;

    EXPECT_TRUE(shortTagA == shortTagA);  // Test same object
    EXPECT_TRUE(shortTagA == shortTagB);  // Test same data #1
    EXPECT_TRUE(shortTagA == shortTagC);  // Test same data #2
    shortTagB.setValue(3);
    EXPECT_FALSE(shortTagA == shortTagB); // Test different data #1
    shortTagC.setName("Test3");
    EXPECT_FALSE(shortTagA == shortTagC); // Test different data #2

    EXPECT_FALSE(shortTagE == endTag);   // Test different types
}

TEST(ShortTag, NotEqual)
{
    nbt::ShortTag shortTagA("Test1", 1);
    nbt::ShortTag shortTagB("Test1", 1);
    nbt::ShortTag shortTagC("Test1", 1);
    nbt::ShortTag shortTagD("Test2", 2);
    nbt::ShortTag shortTagE;
    nbt::EndTag endTag;

    EXPECT_FALSE(shortTagA != shortTagA);  // Test same object
    EXPECT_FALSE(shortTagA != shortTagB);  // Test same data #1
    EXPECT_FALSE(shortTagA != shortTagC);  // Test same data #2
    shortTagB.setValue(3);
    EXPECT_TRUE(shortTagA != shortTagB); // Test different data #1
    shortTagC.setName("Test3");
    EXPECT_TRUE(shortTagA != shortTagC); // Test different data #2

    EXPECT_TRUE(shortTagE != endTag);   // Test different types
}

TEST(ShortTag, getType)
{
    nbt::ShortTag shortTag;
    EXPECT_EQ(nbt::TagType::Short, shortTag.getType());
}

TEST(ShortTag, getData)
{
    const std::vector<unsigned char> testData = {
        0x02, 0x00, 0x09, 0x73, 0x68, 0x6F, 0x72, 0x74,
        0x54, 0x65, 0x73, 0x74, 0x7F, 0xFF
    };

    nbt::ShortTag shortTag("shortTest", 32767);
    std::vector<unsigned char> data = shortTag.getData(false);

    EXPECT_EQ(data.size(), testData.size());
    EXPECT_THAT(data, ::testing::ElementsAreArray(testData));

    std::vector<unsigned char> data2 = shortTag.getData(true);
    EXPECT_EQ(2, data2.size());
    EXPECT_THAT(data2, ::testing::ElementsAreArray(testData.begin() + 12, testData.end()));
}

TEST(ShortTag, getValue)
{
    int16_t value = 12390;
    int16_t value2 = -12878;
    nbt::ShortTag shortTag;
    EXPECT_EQ(0, shortTag.getValue());
    shortTag.setValue(value);
    EXPECT_EQ(value, shortTag.getValue());
    shortTag.setValue(value2);
    EXPECT_EQ(value2, shortTag.getValue());
}

TEST(ShortTag, setValue)
{
    int16_t value = 12311;
    int16_t value2 = -12834;
    nbt::ShortTag shortTag;
    EXPECT_EQ(0, shortTag.getValue());
    shortTag.setValue(value);
    EXPECT_EQ(value, shortTag.getValue());
    shortTag.setValue(value2);
    EXPECT_EQ(value2, shortTag.getValue());
}

TEST(ShortTag, tag_cast)
{
    nbt::AbstractTag *testTag = new nbt::ShortTag("A", 2);

    nbt::ShortTag *otherTag = tag_cast<nbt::ShortTag*>(testTag);
    EXPECT_EQ(otherTag, testTag);

    nbt::IntTag *nullTag = tag_cast<nbt::IntTag*>(testTag);
    EXPECT_EQ(nullTag, nullptr);
}