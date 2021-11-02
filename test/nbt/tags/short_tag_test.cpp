#include "nbt/tags/short_tag.hpp"
#include "nbt/tags/end_tag.hpp"

// gtest
#include <gtest/gtest.h>

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
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ShortTag, MoveConstructor)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ShortTag, CopyAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ShortTag, MoveAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(ShortTag, clone)
{
    nbt::ShortTag shortTagA("Test1", 1);

    nbt::ShortTag *shortTagB = (nbt::ShortTag *)shortTagA.clone();
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
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
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