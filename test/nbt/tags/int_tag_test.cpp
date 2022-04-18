// AwesomeMC
#include <AwesomeMC/nbt/tags/int_tag.hpp>
#include <AwesomeMC/nbt/tags/byte_tag.hpp>
#include <AwesomeMC/nbt/tags/end_tag.hpp>

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// STL
#include <type_traits>

TEST(IntTag, value_type)
{
    bool check = std::is_same<int32_t, amc::IntTag::value_type>::value;
    EXPECT_TRUE(check);
}

TEST(IntTag, Constructor)
{
    amc::IntTag intTag;
    EXPECT_STREQ("", intTag.getName().c_str());
    EXPECT_EQ(amc::TagType::Int, intTag.getType());
    EXPECT_EQ(0, intTag.getValue());
}

TEST(IntTag, Constructor_2)
{
    amc::IntTag intTag("TagName");
    EXPECT_STREQ("TagName", intTag.getName().c_str());
    EXPECT_EQ(amc::TagType::Int, intTag.getType());
    EXPECT_EQ(0, intTag.getValue());
}

TEST(IntTag, Constructor_3)
{
    int32_t value = 0x012345678;
    amc::IntTag intTag(value);
    EXPECT_STREQ("", intTag.getName().c_str());
    EXPECT_EQ(amc::TagType::Int, intTag.getType());
    EXPECT_EQ(value, intTag.getValue());
}

TEST(IntTag, Constructor_4)
{
    int32_t value = 0x81234567;
    amc::IntTag intTag("TagName", value);
    EXPECT_STREQ("TagName", intTag.getName().c_str());
    EXPECT_EQ(amc::TagType::Int, intTag.getType());
    EXPECT_EQ(value, intTag.getValue());
}

TEST(IntTag, CopyConstructor)
{
    std::string name = "CopyConstructor";
    int32_t value = 0x12345678;

    // Init
    amc::IntTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Test Copy
    amc::IntTag tagB(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_EQ(tagB.getValue(), tagA.getValue());
}

TEST(IntTag, MoveConstructor)
{
    std::string name = "MoveConstructor";
    int32_t value = 0x12345679;

    // Init
    amc::IntTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Test Move
    amc::IntTag tagB(std::move(tagA));
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_EQ(tagB.getValue(), value);
}

TEST(IntTag, CopyAssignment)
{
    std::string name = "CopyAssignment";
    int32_t value = 0x1234567A;

    // Init A
    amc::IntTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Init B
    amc::IntTag tagB;
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
    int32_t value = 0x1234567B;

    // Init A
    amc::IntTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Init B
    amc::IntTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_EQ(tagB.getValue(), 0);

    // Test Move Assignment
    tagB = std::move(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_EQ(tagB.getValue(), value);
}

TEST(IntTag, clone)
{
    amc::IntTag intTagA("Test1", 0x81234567);

    amc::IntTag *intTagB = tag_cast<amc::IntTag*>(intTagA.clone());
    EXPECT_TRUE(intTagA == *intTagB);

    delete intTagB;
}

TEST(IntTag, Equal)
{
    amc::IntTag intTagA("Test1", 0x81234567);
    amc::IntTag intTagB("Test1", 0x81234567);
    amc::IntTag intTagC("Test1", 0x81234567);
    amc::IntTag intTagD("Test2", 2);
    amc::IntTag intTagE;
    amc::EndTag endTag;

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
    amc::IntTag intTagA("Test1", 0x01234567);
    amc::IntTag intTagB("Test1", 0x01234567);
    amc::IntTag intTagC("Test1", 0x01234567);
    amc::IntTag intTagD("Test2", 2);
    amc::IntTag intTagE;
    amc::EndTag endTag;

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
    amc::IntTag intTag;
    EXPECT_EQ(amc::TagType::Int, intTag.getType());
}

TEST(IntTag, getData)
{
    const std::vector<unsigned char> testData = {
        0x03, 0x00, 0x07, 0x69, 0x6E, 0x74, 0x54, 0x65,
        0x73, 0x74, 0x7F, 0xFF, 0xFF, 0xFF
    };

    amc::IntTag intTag("intTest", 2147483647);
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
    amc::IntTag intTag;
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
    amc::IntTag intTag;
    EXPECT_EQ(0, intTag.getValue());
    intTag.setValue(value);
    EXPECT_EQ(value, intTag.getValue());
    intTag.setValue(value2);
    EXPECT_EQ(value2, intTag.getValue());
}

TEST(IntTag, tag_cast)
{
    amc::AbstractTag *testTag = new amc::IntTag("A", 2);

    amc::IntTag *otherTag = tag_cast<amc::IntTag*>(testTag);
    EXPECT_EQ(otherTag, testTag);

    amc::ByteTag *nullTag = tag_cast<amc::ByteTag*>(testTag);
    EXPECT_EQ(nullTag, nullptr);

    delete testTag;
}