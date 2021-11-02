#include "nbt/tags/int_tag.hpp"
#include "nbt/tags/end_tag.hpp"

// gtest
#include <gtest/gtest.h>

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
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(IntTag, MoveConstructor)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(IntTag, CopyAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(IntTag, MoveAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(IntTag, clone)
{
    nbt::IntTag intTagA("Test1", 0x81234567);

    nbt::IntTag *intTagB = (nbt::IntTag *)intTagA.clone();
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
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
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