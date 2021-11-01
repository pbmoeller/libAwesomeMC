#include "nbt/float_tag.hpp"
#include "nbt/end_tag.hpp"

// gtest
#include <gtest/gtest.h>

TEST(FloatTag, Constructor)
{
    nbt::FloatTag floatTag;
    EXPECT_STREQ("", floatTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Float, floatTag.getType());
    EXPECT_EQ(0.0f, floatTag.getValue());
}

TEST(FloatTag, Constructor_2)
{
    nbt::FloatTag floatTag("TagName");
    EXPECT_STREQ("TagName", floatTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Float, floatTag.getType());
    EXPECT_EQ(0.0f, floatTag.getValue());
}

TEST(FloatTag, Constructor_3)
{
    float value = 3.9f;
    nbt::FloatTag floatTag(value);
    EXPECT_STREQ("", floatTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Float, floatTag.getType());
    EXPECT_EQ(value, floatTag.getValue());
}

TEST(FloatTag, Constructor_4)
{
    float value = -1.2f;
    nbt::FloatTag floatTag("TagName", value);
    EXPECT_STREQ("TagName", floatTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::Float, floatTag.getType());
    EXPECT_EQ(value, floatTag.getValue());
}

TEST(FloatTag, CopyConstructor)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(FloatTag, MoveConstructor)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(FloatTag, CopyAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(FloatTag, MoveAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(FloatTag, clone)
{
    nbt::FloatTag floatTagA("Test1", 3.14f);

    nbt::FloatTag *floatTagB = (nbt::FloatTag *)floatTagA.clone();
    EXPECT_TRUE(floatTagA == *floatTagB);
}

TEST(FloatTag, Equal)
{
    nbt::FloatTag floatTagA("Test1", 3.14f);
    nbt::FloatTag floatTagB("Test1", 3.14f);
    nbt::FloatTag floatTagC("Test1", 3.14f);
    nbt::FloatTag floatTagD("Test2", 2);
    nbt::FloatTag floatTagE;
    nbt::EndTag endTag;

    EXPECT_TRUE(floatTagA == floatTagA);  // Test same object
    EXPECT_TRUE(floatTagA == floatTagB);  // Test same data #1
    EXPECT_TRUE(floatTagA == floatTagC);  // Test same data #2
    floatTagB.setValue(3);
    EXPECT_FALSE(floatTagA == floatTagB); // Test different data #1
    floatTagC.setName("Test3");
    EXPECT_FALSE(floatTagA == floatTagC); // Test different data #2

    EXPECT_FALSE(floatTagE == endTag);   // Test different types
}

TEST(FloatTag, NotEqual)
{
    nbt::FloatTag floatTagA("Test1", -2.6f);
    nbt::FloatTag floatTagB("Test1", -2.6f);
    nbt::FloatTag floatTagC("Test1", -2.6f);
    nbt::FloatTag floatTagD("Test2", 2);
    nbt::FloatTag floatTagE;
    nbt::EndTag endTag;

    EXPECT_FALSE(floatTagA != floatTagA);  // Test same object
    EXPECT_FALSE(floatTagA != floatTagB);  // Test same data #1
    EXPECT_FALSE(floatTagA != floatTagC);  // Test same data #2
    floatTagB.setValue(3);
    EXPECT_TRUE(floatTagA != floatTagB); // Test different data #1
    floatTagC.setName("Test3");
    EXPECT_TRUE(floatTagA != floatTagC); // Test different data #2

    EXPECT_TRUE(floatTagE != endTag);   // Test different types
}

TEST(FloatTag, getType)
{
    nbt::FloatTag floatTag;
    EXPECT_EQ(nbt::TagType::Float, floatTag.getType());
}

TEST(FloatTag, getData)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(FloatTag, getValue)
{
    float value = 12390.f;
    float value2 = -12878.f;
    nbt::FloatTag floatTag;
    EXPECT_EQ(0.0f, floatTag.getValue());
    floatTag.setValue(value);
    EXPECT_EQ(value, floatTag.getValue());
    floatTag.setValue(value2);
    EXPECT_EQ(value2, floatTag.getValue());
}

TEST(FloatTag, setValue)
{
    float value = 12311.f;
    float value2 = -12834.f;
    nbt::FloatTag floatTag;
    EXPECT_EQ(0.0f, floatTag.getValue());
    floatTag.setValue(value);
    EXPECT_EQ(value, floatTag.getValue());
    floatTag.setValue(value2);
    EXPECT_EQ(value2, floatTag.getValue());
}