#include "nbt/tags/string_tag.hpp"
#include "nbt/tags/end_tag.hpp"
#include "nbt/tags/int_tag.hpp"

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

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
    std::string name = "CopyConstructor";
    std::string value = "Value CopyConstructor";

    // Init
    nbt::StringTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_STREQ(tagA.getValue().c_str(), value.c_str());

    // Test Copy
    nbt::StringTag tagB(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_STREQ(tagB.getValue().c_str(), tagA.getValue().c_str());
}

TEST(StringTag, MoveConstructor)
{
    std::string name = "MoveConstructor";
    std::string value = "Value MoveConstructor";

    // Init
    nbt::StringTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_STREQ(tagA.getValue().c_str(), value.c_str());

    // Test Move
    nbt::StringTag tagB(std::move(tagA));
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_STREQ(tagB.getValue().c_str(), value.c_str());
}

TEST(StringTag, CopyAssignment)
{
    std::string name = "CopyAssignment";
    std::string value = "Value CopyAssignment";

    // Init A
    nbt::StringTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_STREQ(tagA.getValue().c_str(), value.c_str());

    // Init B
    nbt::StringTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_STREQ(tagB.getValue().c_str(), "");

    // Test Copy Assignment
    tagB = tagA;
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_STREQ(tagB.getValue().c_str(), tagA.getValue().c_str());
}

TEST(StringTag, MoveAssignment)
{
    std::string name = "MoveAssignment";
    std::string value = "Value MoveAssignment";

    // Init A
    nbt::StringTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_STREQ(tagA.getValue().c_str(), value.c_str());

    // Init B
    nbt::StringTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_STREQ(tagB.getValue().c_str(), "");

    // Test Move Assignment
    tagB = std::move(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_STREQ(tagB.getValue().c_str(), value.c_str());
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
    const std::vector<unsigned char> testData = {
        0x08, 0x00, 0x0A, 0x73, 0x74, 0x72, 0x69, 0x6E,
        0x67, 0x54, 0x65, 0x73, 0x74, 0x00, 0x22, 0x48,
        0x45, 0x4C, 0x4C, 0x4F, 0x20, 0x57, 0x4F, 0x52,
        0x4C, 0x44, 0x20, 0x54, 0x48, 0x49, 0x53, 0x20,
        0x49, 0x53, 0x20, 0x41, 0x20, 0x54, 0x45, 0x53,
        0x54, 0x20, 0x53, 0x54, 0x52, 0x49, 0x4E, 0x47,
        0x21
    };

    nbt::StringTag stringTag("stringTest", "HELLO WORLD THIS IS A TEST STRING!");
    std::vector<unsigned char> data = stringTag.getData(false);

    EXPECT_EQ(data.size(), testData.size());
    EXPECT_THAT(data, ::testing::ElementsAreArray(testData));

    std::vector<unsigned char> data2 = stringTag.getData(true);
    EXPECT_EQ(36, data2.size());
    EXPECT_THAT(data2, ::testing::ElementsAreArray(testData.begin() + 13, testData.end()));
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

TEST(StringTag, tag_cast)
{
    nbt::AbstractTag *testTag = new nbt::StringTag("A", "ABC");

    nbt::StringTag *otherTag = tag_cast<nbt::StringTag*>(testTag);
    EXPECT_EQ(otherTag, testTag);

    nbt::IntTag *nullTag = tag_cast<nbt::IntTag*>(testTag);
    EXPECT_EQ(nullTag, nullptr);
}