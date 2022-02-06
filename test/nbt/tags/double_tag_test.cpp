// AwesomeMC
#include <AwesomeMC/nbt/tags/double_tag.hpp>
#include <AwesomeMC/nbt/tags/end_tag.hpp>
#include <AwesomeMC/nbt/tags/int_tag.hpp>

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(DoubleTag, Constructor)
{
    amc::DoubleTag doubleTag;
    EXPECT_STREQ("", doubleTag.getName().c_str());
    EXPECT_EQ(amc::TagType::Double, doubleTag.getType());
    EXPECT_EQ(0.0, doubleTag.getValue());
}

TEST(DoubleTag, Constructor_2)
{
    amc::DoubleTag doubleTag("TagName");
    EXPECT_STREQ("TagName", doubleTag.getName().c_str());
    EXPECT_EQ(amc::TagType::Double, doubleTag.getType());
    EXPECT_EQ(0.0, doubleTag.getValue());
}

TEST(DoubleTag, Constructor_3)
{
    double value = 3.9999;
    amc::DoubleTag doubleTag(value);
    EXPECT_STREQ("", doubleTag.getName().c_str());
    EXPECT_EQ(amc::TagType::Double, doubleTag.getType());
    EXPECT_EQ(value, doubleTag.getValue());
}

TEST(DoubleTag, Constructor_4)
{
    double value = -1.212424;
    amc::DoubleTag doubleTag("TagName", value);
    EXPECT_STREQ("TagName", doubleTag.getName().c_str());
    EXPECT_EQ(amc::TagType::Double, doubleTag.getType());
    EXPECT_EQ(value, doubleTag.getValue());
}

TEST(DoubleTag, CopyConstructor)
{
    std::string name = "CopyConstructor";
    double value = 1.23456789;

    // Init
    amc::DoubleTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Test Copy
    amc::DoubleTag tagB(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_EQ(tagB.getValue(), tagA.getValue());
}

TEST(DoubleTag, MoveConstructor)
{
    std::string name = "MoveConstructor";
    double value = 1.3e300;

    // Init
    amc::DoubleTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Test Move
    amc::DoubleTag tagB(std::move(tagA));
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_EQ(tagB.getValue(), value);
}

TEST(DoubleTag, CopyAssignment)
{
    std::string name = "CopyAssignment";
    double value = -5.6e-222;

    // Init A
    amc::DoubleTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Init B
    amc::DoubleTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_EQ(tagB.getValue(), 0);

    // Test Copy Assignment
    tagB = tagA;
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_EQ(tagB.getValue(), tagA.getValue());
}

TEST(DoubleTag, MoveAssignment)
{
    std::string name = "MoveAssignment";
    double value = 123456789.123456789123456;

    // Init A
    amc::DoubleTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Init B
    amc::DoubleTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_EQ(tagB.getValue(), 0);

    // Test Move Assignment
    tagB = std::move(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_EQ(tagB.getValue(), value);
}

TEST(DoubleTag, clone)
{
    amc::DoubleTag doubleTagA("Test1", 3.14);

    amc::DoubleTag *doubleTagB = tag_cast<amc::DoubleTag*>(doubleTagA.clone());
    EXPECT_TRUE(doubleTagA == *doubleTagB);

    delete doubleTagB;
}

TEST(DoubleTag, Equal)
{
    amc::DoubleTag doubleTagA("Test1", 3.14);
    amc::DoubleTag doubleTagB("Test1", 3.14);
    amc::DoubleTag doubleTagC("Test1", 3.14);
    amc::DoubleTag doubleTagD("Test2", 2);
    amc::DoubleTag doubleTagE;
    amc::EndTag endTag;

    EXPECT_TRUE(doubleTagA == doubleTagA);  // Test same object
    EXPECT_TRUE(doubleTagA == doubleTagB);  // Test same data #1
    EXPECT_TRUE(doubleTagA == doubleTagC);  // Test same data #2
    doubleTagB.setValue(3.24);
    EXPECT_FALSE(doubleTagA == doubleTagB); // Test different data #1
    doubleTagC.setName("Test3");
    EXPECT_FALSE(doubleTagA == doubleTagC); // Test different data #2

    EXPECT_FALSE(doubleTagE == endTag);   // Test different types
}

TEST(DoubleTag, NotEqual)
{
    amc::DoubleTag doubleTagA("Test1", -2.6);
    amc::DoubleTag doubleTagB("Test1", -2.6);
    amc::DoubleTag doubleTagC("Test1", -2.6);
    amc::DoubleTag doubleTagD("Test2", 2.3);
    amc::DoubleTag doubleTagE;
    amc::EndTag endTag;

    EXPECT_FALSE(doubleTagA != doubleTagA);  // Test same object
    EXPECT_FALSE(doubleTagA != doubleTagB);  // Test same data #1
    EXPECT_FALSE(doubleTagA != doubleTagC);  // Test same data #2
    doubleTagB.setValue(3.3);
    EXPECT_TRUE(doubleTagA != doubleTagB); // Test different data #1
    doubleTagC.setName("Test3");
    EXPECT_TRUE(doubleTagA != doubleTagC); // Test different data #2

    EXPECT_TRUE(doubleTagE != endTag);   // Test different types
}

TEST(DoubleTag, getType)
{
    amc::DoubleTag doubleTag;
    EXPECT_EQ(amc::TagType::Double, doubleTag.getType());
}

TEST(DoubleTag, getData)
{
    const std::vector<unsigned char> testData = {
        0x06, 0x00, 0x0A, 0x64, 0x6F, 0x75, 0x62, 0x6C,
        0x65, 0x54, 0x65, 0x73, 0x74, 0x3F, 0xDF, 0x8F,
        0x6B, 0xBB, 0xFF, 0x6A, 0x5E
    };

    amc::DoubleTag doubleTag("doubleTest", 0.49312871321823148);
    std::vector<unsigned char> data = doubleTag.getData(false);

    EXPECT_EQ(data.size(), testData.size());
    EXPECT_THAT(data, ::testing::ElementsAreArray(testData));

    std::vector<unsigned char> data2 = doubleTag.getData(true);
    EXPECT_EQ(8, data2.size());
    EXPECT_THAT(data2, ::testing::ElementsAreArray(testData.begin() + 13, testData.end()));
}

TEST(DoubleTag, getValue)
{
    double value = 12390.0;
    double value2 = -12878.24;
    amc::DoubleTag doubleTag;
    EXPECT_EQ(0.0, doubleTag.getValue());
    doubleTag.setValue(value);
    EXPECT_EQ(value, doubleTag.getValue());
    doubleTag.setValue(value2);
    EXPECT_EQ(value2, doubleTag.getValue());
}

TEST(DoubleTag, setValue)
{
    double value = 12311.13123;
    double value2 = -12834.183913;
    amc::DoubleTag doubleTag;
    EXPECT_EQ(0.0, doubleTag.getValue());
    doubleTag.setValue(value);
    EXPECT_EQ(value, doubleTag.getValue());
    doubleTag.setValue(value2);
    EXPECT_EQ(value2, doubleTag.getValue());
}

TEST(DoubleTag, tag_cast)
{
    amc::AbstractTag *testTag = new amc::DoubleTag("A", 4.13);

    amc::DoubleTag *otherTag = tag_cast<amc::DoubleTag*>(testTag);
    EXPECT_EQ(otherTag, testTag);

    amc::IntTag *nullTag = tag_cast<amc::IntTag*>(testTag);
    EXPECT_EQ(nullTag, nullptr);

    delete testTag;
}