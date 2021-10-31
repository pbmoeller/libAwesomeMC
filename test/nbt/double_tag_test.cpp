#include "nbt/double_tag.hpp"
#include "nbt/end_tag.hpp"

// gtest
#include <gtest/gtest.h>

TEST(DoubleTag, Constructor)
{
    nbt::DoubleTag doubleTag;
    EXPECT_STREQ("", doubleTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Double, doubleTag.getType());
    EXPECT_EQ(0.0, doubleTag.getValue());
}

TEST(DoubleTag, Constructor_2)
{
    nbt::DoubleTag doubleTag("TagName");
    EXPECT_STREQ("TagName", doubleTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Double, doubleTag.getType());
    EXPECT_EQ(0.0, doubleTag.getValue());
}

TEST(DoubleTag, Constructor_3)
{
    double value = 3.9999;
    nbt::DoubleTag doubleTag(value);
    EXPECT_STREQ("", doubleTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Double, doubleTag.getType());
    EXPECT_EQ(value, doubleTag.getValue());
}

TEST(DoubleTag, Constructor_4)
{
    double value = -1.212424;
    nbt::DoubleTag doubleTag("TagName", value);
    EXPECT_STREQ("TagName", doubleTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Double, doubleTag.getType());
    EXPECT_EQ(value, doubleTag.getValue());
}

TEST(DoubleTag, CopyConstructor)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(DoubleTag, MoveConstructor)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(DoubleTag, CopyAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(DoubleTag, MoveAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(DoubleTag, Equal)
{
    nbt::DoubleTag doubleTagA("Test1", 3.14);
    nbt::DoubleTag doubleTagB("Test1", 3.14);
    nbt::DoubleTag doubleTagC("Test1", 3.14);
    nbt::DoubleTag doubleTagD("Test2", 2);
    nbt::DoubleTag doubleTagE;
    nbt::EndTag endTag;

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
    nbt::DoubleTag doubleTagA("Test1", -2.6);
    nbt::DoubleTag doubleTagB("Test1", -2.6);
    nbt::DoubleTag doubleTagC("Test1", -2.6);
    nbt::DoubleTag doubleTagD("Test2", 2.3);
    nbt::DoubleTag doubleTagE;
    nbt::EndTag endTag;

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
    nbt::DoubleTag doubleTag;
    EXPECT_EQ(nbt::TagType::Double, doubleTag.getType());
}

TEST(DoubleTag, getData)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(DoubleTag, getValue)
{
    double value = 12390.0;
    double value2 = -12878.24;
    nbt::DoubleTag doubleTag;
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
    nbt::DoubleTag doubleTag;
    EXPECT_EQ(0.0, doubleTag.getValue());
    doubleTag.setValue(value);
    EXPECT_EQ(value, doubleTag.getValue());
    doubleTag.setValue(value2);
    EXPECT_EQ(value2, doubleTag.getValue());
}