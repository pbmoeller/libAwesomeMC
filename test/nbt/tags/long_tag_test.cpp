// AwesomeMC
#include <AwesomeMC/nbt/tags/long_tag.hpp>
#include <AwesomeMC/nbt/tags/end_tag.hpp>
#include <AwesomeMC/nbt/tags/int_tag.hpp>

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// STL
#include <type_traits>

TEST(LongTag, value_type)
{
    bool check = std::is_same<int64_t, amc::LongTag::value_type>::value;
    EXPECT_TRUE(check);
}

TEST(LongTag, Constructor)
{
    amc::LongTag longTag;
    EXPECT_STREQ("", longTag.getName().c_str());
    EXPECT_EQ(amc::TagType::Long, longTag.getType());
    EXPECT_EQ(0, longTag.getValue());
}

TEST(LongTag, Constructor_2)
{
    amc::LongTag longTag("TagName");
    EXPECT_STREQ("TagName", longTag.getName().c_str());
    EXPECT_EQ(amc::TagType::Long, longTag.getType());
    EXPECT_EQ(0, longTag.getValue());
}

TEST(LongTag, Constructor_3)
{
    int64_t value = 0x0123456789ABCDEF;
    amc::LongTag longTag(value);
    EXPECT_STREQ("", longTag.getName().c_str());
    EXPECT_EQ(amc::TagType::Long, longTag.getType());
    EXPECT_EQ(value, longTag.getValue());
}

TEST(LongTag, Constructor_4)
{
    int64_t value = 0x8123456789ABCDEF;
    amc::LongTag longTag("TagName", value);
    EXPECT_STREQ("TagName", longTag.getName().c_str());
    EXPECT_EQ(amc::TagType::Long, longTag.getType());
    EXPECT_EQ(value, longTag.getValue());
}

TEST(LongTag, CopyConstructor)
{
    std::string name = "CopyConstructor";
    int64_t value = 0x0123456789ABCDEF;

    // Init
    amc::LongTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Test Copy
    amc::LongTag tagB(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_EQ(tagB.getValue(), tagA.getValue());
}

TEST(LongTag, MoveConstructor)
{
    std::string name = "MoveConstructor";
    int64_t value = 0x0123456789ABCDEE;

    // Init
    amc::LongTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Test Move
    amc::LongTag tagB(std::move(tagA));
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_EQ(tagB.getValue(), tagA.getValue());
}

TEST(LongTag, CopyAssignment)
{
    std::string name = "CopyAssignment";
    int64_t value = 0x0123456789ABCDED;

    // Init A
    amc::LongTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Init B
    amc::LongTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_EQ(tagB.getValue(), 0);

    // Test Copy Assignment
    tagB = tagA;
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_EQ(tagB.getValue(), tagA.getValue());
}

TEST(LongTag, MoveAssignment)
{
    std::string name = "MoveAssignment";
    int64_t value = 0x0123456789ABCDEC;

    // Init A
    amc::LongTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Init B
    amc::LongTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_EQ(tagB.getValue(), 0);

    // Test Move Assignment
    tagB = std::move(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_EQ(tagB.getValue(), value);
}

TEST(LongTag, clone)
{
    amc::LongTag longTagA("Test1", 0x8123456789ABCDEF);

    amc::LongTag *longTagB = tag_cast<amc::LongTag*>(longTagA.clone());
    EXPECT_TRUE(longTagA == *longTagB);

    delete longTagB;
}

TEST(LongTag, Equal)
{
    amc::LongTag longTagA("Test1", 0x8123456789ABCDEF);
    amc::LongTag longTagB("Test1", 0x8123456789ABCDEF);
    amc::LongTag longTagC("Test1", 0x8123456789ABCDEF);
    amc::LongTag longTagD("Test2", 2);
    amc::LongTag longTagE;
    amc::EndTag endTag;

    EXPECT_TRUE(longTagA == longTagA);  // Test same object
    EXPECT_TRUE(longTagA == longTagB);  // Test same data #1
    EXPECT_TRUE(longTagA == longTagC);  // Test same data #2
    longTagB.setValue(3);
    EXPECT_FALSE(longTagA == longTagB); // Test different data #1
    longTagC.setName("Test3");
    EXPECT_FALSE(longTagA == longTagC); // Test different data #2

    EXPECT_FALSE(longTagE == endTag);   // Test different types
}

TEST(LongTag, NotEqual)
{
    amc::LongTag longTagA("Test1", 0x0123456789ABCDEF);
    amc::LongTag longTagB("Test1", 0x0123456789ABCDEF);
    amc::LongTag longTagC("Test1", 0x0123456789ABCDEF);
    amc::LongTag longTagD("Test2", 2);
    amc::LongTag longTagE;
    amc::EndTag endTag;

    EXPECT_FALSE(longTagA != longTagA);  // Test same object
    EXPECT_FALSE(longTagA != longTagB);  // Test same data #1
    EXPECT_FALSE(longTagA != longTagC);  // Test same data #2
    longTagB.setValue(3);
    EXPECT_TRUE(longTagA != longTagB); // Test different data #1
    longTagC.setName("Test3");
    EXPECT_TRUE(longTagA != longTagC); // Test different data #2

    EXPECT_TRUE(longTagE != endTag);   // Test different types
}

TEST(LongTag, getType)
{
    amc::LongTag longTag;
    EXPECT_EQ(amc::TagType::Long, longTag.getType());
}

TEST(LongTag, getData)
{
    const std::vector<unsigned char> testData = {
        0x04, 0x00, 0x08, 0x6C, 0x6F, 0x6E, 0x67, 0x54,
        0x65, 0x73, 0x74, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 
        0xFF, 0xFF, 0xFF
    };

    amc::LongTag longTag("longTest", 9223372036854775807);
    std::vector<unsigned char> data = longTag.getData(false);

    EXPECT_EQ(data.size(), testData.size());
    EXPECT_THAT(data, ::testing::ElementsAreArray(testData));

    std::vector<unsigned char> data2 = longTag.getData(true);
    EXPECT_EQ(8, data2.size());
    EXPECT_THAT(data2, ::testing::ElementsAreArray(testData.begin() + 11, testData.end()));
}

TEST(LongTag, getValue)
{
    int64_t value = 12390;
    int64_t value2 = -12878;
    amc::LongTag longTag;
    EXPECT_EQ(0, longTag.getValue());
    longTag.setValue(value);
    EXPECT_EQ(value, longTag.getValue());
    longTag.setValue(value2);
    EXPECT_EQ(value2, longTag.getValue());
}

TEST(LongTag, setValue)
{
    int64_t value = 12311;
    int64_t value2 = -12834;
    amc::LongTag longTag;
    EXPECT_EQ(0, longTag.getValue());
    longTag.setValue(value);
    EXPECT_EQ(value, longTag.getValue());
    longTag.setValue(value2);
    EXPECT_EQ(value2, longTag.getValue());
}

TEST(LongTag, tag_cast)
{
    amc::AbstractTag *testTag = new amc::LongTag("A", 2);

    amc::LongTag *otherTag = tag_cast<amc::LongTag*>(testTag);
    EXPECT_EQ(otherTag, testTag);

    amc::IntTag *nullTag = tag_cast<amc::IntTag*>(testTag);
    EXPECT_EQ(nullTag, nullptr);

    delete testTag;
}