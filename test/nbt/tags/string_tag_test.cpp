#include "nbt/tags/string_tag.hpp"
#include "nbt/tags/end_tag.hpp"

// gtest
#include <gtest/gtest.h>

TEST(StringTag, Constructor)
{
    nbt::StringTag stringTag;
    EXPECT_STREQ("", stringTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::String, stringTag.getType());
    EXPECT_STREQ("", stringTag.getValue().c_str());
}

TEST(StringTag, Constructor_2)
{
    std::string str("value");
    nbt::StringTag stringTag(str);
    EXPECT_STREQ("", stringTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::String, stringTag.getType());
    EXPECT_STREQ(str.c_str(), stringTag.getValue().c_str());
}

TEST(StringTag, Constructor_3)
{
    std::string str("value");
    nbt::StringTag stringTag("TagName", str);
    EXPECT_STREQ("TagName", stringTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::String, stringTag.getType());
    EXPECT_STREQ(str.c_str(), stringTag.getValue().c_str());
}

TEST(StringTag, CopyConstructor)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(StringTag, MoveConstructor)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(StringTag, CopyAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(StringTag, MoveAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(StringTag, clone)
{
    nbt::StringTag stringTagA("Test1", "ABC");

    nbt::StringTag *stringTagB = (nbt::StringTag *)stringTagA.clone();
    EXPECT_TRUE(stringTagA == *stringTagB);
}

TEST(StringTag, Equal)
{
    nbt::StringTag stringTagA("Test1", "ABC");
    nbt::StringTag stringTagB("Test1", "ABC");
    nbt::StringTag stringTagC("Test1", "ABC");
    nbt::StringTag stringTagD("Test2", "/adsjakjd");
    nbt::StringTag stringTagE;
    nbt::EndTag endTag;

    EXPECT_TRUE(stringTagA == stringTagA);  // Test same object
    EXPECT_TRUE(stringTagA == stringTagB);  // Test same data #1
    EXPECT_TRUE(stringTagA == stringTagC);  // Test same data #2
    stringTagB.setValue("as");
    EXPECT_FALSE(stringTagA == stringTagB); // Test different data #1
    stringTagC.setName("Test3");
    EXPECT_FALSE(stringTagA == stringTagC); // Test different data #2

    EXPECT_FALSE(stringTagE == endTag);   // Test different types
}

TEST(StringTag, NotEqual)
{
    nbt::StringTag stringTagA("Test1", "ABC");
    nbt::StringTag stringTagB("Test1", "ABC");
    nbt::StringTag stringTagC("Test1", "ABC");
    nbt::StringTag stringTagD("Test2", "/adsjakjd");
    nbt::StringTag stringTagE;
    nbt::EndTag endTag;

    EXPECT_FALSE(stringTagA != stringTagA);  // Test same object
    EXPECT_FALSE(stringTagA != stringTagB);  // Test same data #1
    EXPECT_FALSE(stringTagA != stringTagC);  // Test same data #2
    stringTagB.setValue("as");
    EXPECT_TRUE(stringTagA != stringTagB); // Test different data #1
    stringTagC.setName("Test3");
    EXPECT_TRUE(stringTagA != stringTagC); // Test different data #2

    EXPECT_TRUE(stringTagE != endTag);   // Test different types
}

TEST(StringTag, getType)
{
    nbt::StringTag stringTag;
    EXPECT_EQ(nbt::TagType::String, stringTag.getType());
}

TEST(StringTag, getData)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(StringTag, getValue)
{
    std::string value("123");
    std::string value2("TestString");
    nbt::StringTag stringTag;
    EXPECT_STREQ("", stringTag.getValue().c_str());
    stringTag.setValue(value);
    EXPECT_STREQ(value.c_str(), stringTag.getValue().c_str());
    stringTag.setValue(value2);
    EXPECT_STREQ(value2.c_str(), stringTag.getValue().c_str());
}

TEST(StringTag, setValue)
{
    std::string value("123  other string");
    std::string value2("TestString#2");
    nbt::StringTag stringTag;
    EXPECT_STREQ("", stringTag.getValue().c_str());
    stringTag.setValue(value);
    EXPECT_STREQ(value.c_str(), stringTag.getValue().c_str());
    stringTag.setValue(value2);
    EXPECT_STREQ(value2.c_str(), stringTag.getValue().c_str());
}