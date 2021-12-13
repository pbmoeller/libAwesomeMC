#include "nbt/tags/float_tag.hpp"
#include "nbt/tags/end_tag.hpp"

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
    std::string name = "CopyConstructor";
    float value = 1.34e4f;

    // Init
    nbt::FloatTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Test Copy
    nbt::FloatTag tagB(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_EQ(tagB.getValue(), tagA.getValue());
}

TEST(FloatTag, MoveConstructor)
{
    std::string name = "MoveConstructor";
    float value = 1.34e-4f;

    // Init
    nbt::FloatTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Test Move
    nbt::FloatTag tagB(std::move(tagA));
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_EQ(tagB.getValue(), value);
}

TEST(FloatTag, CopyAssignment)
{
    std::string name = "CopyAssignment";
    float value = 1.34e38f;

    // Init A
    nbt::FloatTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Init B
    nbt::FloatTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_EQ(tagB.getValue(), 0);

    // Test Copy Assignment
    tagB = tagA;
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_EQ(tagB.getValue(), tagA.getValue());
}

TEST(FloatTag, MoveAssignment)
{
    std::string name = "MoveAssignment";
    float value = -1.34e-15f;

    // Init A
    nbt::FloatTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_EQ(tagA.getValue(), value);

    // Init B
    nbt::FloatTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_EQ(tagB.getValue(), 0);

    // Test Move Assignment
    tagB = std::move(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_EQ(tagB.getValue(), value);
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