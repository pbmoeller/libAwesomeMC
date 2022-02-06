// AwesomeMC
#include <AwesomeMC/nbt/tags/short_tag.hpp>
#include <AwesomeMC/nbt/tags/end_tag.hpp>
#include <AwesomeMC/nbt/tags/int_tag.hpp>

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(ShortTag, Constructor)
{
    amc::ShortTag shortTag;
    EXPECT_STREQ("", shortTag.getName().c_str());
    EXPECT_EQ(amc::TagType::Short, shortTag.getType());
    EXPECT_EQ(0, shortTag.getValue());
}

TEST(ShortTag, Constructor_2)
{
    amc::ShortTag shortTag("TagName");
    EXPECT_STREQ("TagName", shortTag.getName().c_str());
    EXPECT_EQ(amc::TagType::Short, shortTag.getType());
    EXPECT_EQ(0, shortTag.getValue());
}

TEST(ShortTag, Constructor_3)
{
    int16_t value = 12345;
    amc::ShortTag shortTag(value);
    EXPECT_STREQ("", shortTag.getName().c_str());
    EXPECT_EQ(amc::TagType::Short, shortTag.getType());
    EXPECT_EQ(value, shortTag.getValue());
}

TEST(ShortTag, Constructor_4)
{
    int16_t value = -5001;
    amc::ShortTag shortTag("TagName", value);
    EXPECT_STREQ("TagName", shortTag.getName().c_str());
    EXPECT_EQ(amc::TagType::Short, shortTag.getType());
    EXPECT_EQ(value, shortTag.getValue());
}

TEST(ShortTag, CopyConstructor)
{
    std::string name = "CopyConstructor";
    int16_t value = 0x1234;

    // Init
    amc::ShortTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Test Copy
    amc::ShortTag tagB(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_EQ(tagB.getValue(), tagA.getValue());
}

TEST(ShortTag, MoveConstructor)
{
    std::string name = "MoveConstructor";
    int16_t value = 0x1235;

    // Init
    amc::ShortTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Test Move
    amc::ShortTag tagB(std::move(tagA));
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_EQ(tagB.getValue(), value);
}

TEST(ShortTag, CopyAssignment)
{
    std::string name = "CopyAssignment";
    int16_t value = 0x1237;

    // Init A
    amc::ShortTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Init B
    amc::ShortTag tagB;
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
    int16_t value = 0x1238;

    // Init A
    amc::ShortTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Init B
    amc::ShortTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_EQ(tagB.getValue(), 0);

    // Test Move Assignment
    tagB = std::move(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_EQ(tagB.getValue(), value);
}

TEST(ShortTag, clone)
{
    amc::ShortTag shortTagA("Test1", 1);

    amc::ShortTag *shortTagB = tag_cast<amc::ShortTag*>(shortTagA.clone());
    EXPECT_TRUE(shortTagA == *shortTagB);

    delete shortTagB;
}

TEST(ShortTag, Equal)
{
    amc::ShortTag shortTagA("Test1", 1);
    amc::ShortTag shortTagB("Test1", 1);
    amc::ShortTag shortTagC("Test1", 1);
    amc::ShortTag shortTagD("Test2", 2);
    amc::ShortTag shortTagE;
    amc::EndTag endTag;

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
    amc::ShortTag shortTagA("Test1", 1);
    amc::ShortTag shortTagB("Test1", 1);
    amc::ShortTag shortTagC("Test1", 1);
    amc::ShortTag shortTagD("Test2", 2);
    amc::ShortTag shortTagE;
    amc::EndTag endTag;

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
    amc::ShortTag shortTag;
    EXPECT_EQ(amc::TagType::Short, shortTag.getType());
}

TEST(ShortTag, getData)
{
    const std::vector<unsigned char> testData = {
        0x02, 0x00, 0x09, 0x73, 0x68, 0x6F, 0x72, 0x74,
        0x54, 0x65, 0x73, 0x74, 0x7F, 0xFF
    };

    amc::ShortTag shortTag("shortTest", 32767);
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
    amc::ShortTag shortTag;
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
    amc::ShortTag shortTag;
    EXPECT_EQ(0, shortTag.getValue());
    shortTag.setValue(value);
    EXPECT_EQ(value, shortTag.getValue());
    shortTag.setValue(value2);
    EXPECT_EQ(value2, shortTag.getValue());
}

TEST(ShortTag, tag_cast)
{
    amc::AbstractTag *testTag = new amc::ShortTag("A", 2);

    amc::ShortTag *otherTag = tag_cast<amc::ShortTag*>(testTag);
    EXPECT_EQ(otherTag, testTag);

    amc::IntTag *nullTag = tag_cast<amc::IntTag*>(testTag);
    EXPECT_EQ(nullTag, nullptr);

    delete testTag;
}