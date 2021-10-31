#include "nbt/long_tag.hpp"
#include "nbt/end_tag.hpp"

// gtest
#include <gtest/gtest.h>

TEST(LongTag, Constructor)
{
    nbt::LongTag longTag;
    EXPECT_STREQ("", longTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Long, longTag.getType());
    EXPECT_EQ(0, longTag.getValue());
}

TEST(LongTag, Constructor_2)
{
    nbt::LongTag longTag("TagName");
    EXPECT_STREQ("TagName", longTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Long, longTag.getType());
    EXPECT_EQ(0, longTag.getValue());
}

TEST(LongTag, Constructor_3)
{
    int64_t value = 0x0123456789ABCDEF;
    nbt::LongTag longTag(value);
    EXPECT_STREQ("", longTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Long, longTag.getType());
    EXPECT_EQ(value, longTag.getValue());
}

TEST(LongTag, Constructor_4)
{
    int64_t value = 0x8123456789ABCDEF;
    nbt::LongTag longTag("TagName", value);
    EXPECT_STREQ("TagName", longTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Long, longTag.getType());
    EXPECT_EQ(value, longTag.getValue());
}

TEST(LongTag, CopyConstructor)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(LongTag, MoveConstructor)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(LongTag, CopyAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(LongTag, MoveAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(LongTag, Equal)
{
    nbt::LongTag longTagA("Test1", 0x8123456789ABCDEF);
    nbt::LongTag longTagB("Test1", 0x8123456789ABCDEF);
    nbt::LongTag longTagC("Test1", 0x8123456789ABCDEF);
    nbt::LongTag longTagD("Test2", 2);
    nbt::LongTag longTagE;
    nbt::EndTag endTag;

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
    nbt::LongTag longTagA("Test1", 0x0123456789ABCDEF);
    nbt::LongTag longTagB("Test1", 0x0123456789ABCDEF);
    nbt::LongTag longTagC("Test1", 0x0123456789ABCDEF);
    nbt::LongTag longTagD("Test2", 2);
    nbt::LongTag longTagE;
    nbt::EndTag endTag;

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
    nbt::LongTag longTag;
    EXPECT_EQ(nbt::TagType::Long, longTag.getType());
}

TEST(LongTag, getData)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(LongTag, getValue)
{
    int64_t value = 12390;
    int64_t value2 = -12878;
    nbt::LongTag longTag;
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
    nbt::LongTag longTag;
    EXPECT_EQ(0, longTag.getValue());
    longTag.setValue(value);
    EXPECT_EQ(value, longTag.getValue());
    longTag.setValue(value2);
    EXPECT_EQ(value2, longTag.getValue());
}