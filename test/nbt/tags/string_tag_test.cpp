// AwesomeMC
#include <AwesomeMC/nbt/tags/string_tag.hpp>
#include <AwesomeMC/nbt/tags/end_tag.hpp>
#include <AwesomeMC/nbt/tags/int_tag.hpp>

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// STL
#include <type_traits>

TEST(StringTag, value_type)
{
    bool check = std::is_same<std::string, amc::StringTag::value_type>::value;
    EXPECT_TRUE(check);
}

TEST(StringTag, Constructor)
{
    amc::StringTag stringTag;
    EXPECT_STREQ("", stringTag.getName().c_str());
    EXPECT_EQ(amc::TagType::String, stringTag.getType());
    EXPECT_STREQ("", stringTag.getValue().c_str());
}

TEST(StringTag, Constructor_2)
{
    std::string str("value");
    amc::StringTag stringTag(str);
    EXPECT_STREQ("", stringTag.getName().c_str());
    EXPECT_EQ(amc::TagType::String, stringTag.getType());
    EXPECT_STREQ(str.c_str(), stringTag.getValue().c_str());
}

TEST(StringTag, Constructor_3)
{
    std::string str("value");
    amc::StringTag stringTag("TagName", str);
    EXPECT_STREQ("TagName", stringTag.getName().c_str());
    EXPECT_EQ(amc::TagType::String, stringTag.getType());
    EXPECT_STREQ(str.c_str(), stringTag.getValue().c_str());
}

TEST(StringTag, CopyConstructor)
{
    std::string name = "CopyConstructor";
    std::string value = "Value CopyConstructor";

    // Init
    amc::StringTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_STREQ(tagA.getValue().c_str(), value.c_str());

    // Test Copy
    amc::StringTag tagB(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_STREQ(tagB.getValue().c_str(), tagA.getValue().c_str());
}

TEST(StringTag, MoveConstructor)
{
    std::string name = "MoveConstructor";
    std::string value = "Value MoveConstructor";

    // Init
    amc::StringTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_STREQ(tagA.getValue().c_str(), value.c_str());

    // Test Move
    amc::StringTag tagB(std::move(tagA));
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_STREQ(tagB.getValue().c_str(), value.c_str());
}

TEST(StringTag, CopyAssignment)
{
    std::string name = "CopyAssignment";
    std::string value = "Value CopyAssignment";

    // Init A
    amc::StringTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_STREQ(tagA.getValue().c_str(), value.c_str());

    // Init B
    amc::StringTag tagB;
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
    amc::StringTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_STREQ(tagA.getValue().c_str(), value.c_str());

    // Init B
    amc::StringTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_STREQ(tagB.getValue().c_str(), "");

    // Test Move Assignment
    tagB = std::move(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_STREQ(tagB.getValue().c_str(), value.c_str());
}

TEST(StringTag, clone)
{
    amc::StringTag stringTagA("Test1", "ABC");

    amc::StringTag *stringTagB = tag_cast<amc::StringTag*>(stringTagA.clone());
    EXPECT_TRUE(stringTagA == *stringTagB);

    delete stringTagB;
}

TEST(StringTag, Equal)
{
    amc::StringTag stringTagA("Test1", "ABC");
    amc::StringTag stringTagB("Test1", "ABC");
    amc::StringTag stringTagC("Test1", "ABC");
    amc::StringTag stringTagD("Test2", "/adsjakjd");
    amc::StringTag stringTagE;
    amc::EndTag endTag;

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
    amc::StringTag stringTagA("Test1", "ABC");
    amc::StringTag stringTagB("Test1", "ABC");
    amc::StringTag stringTagC("Test1", "ABC");
    amc::StringTag stringTagD("Test2", "/adsjakjd");
    amc::StringTag stringTagE;
    amc::EndTag endTag;

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
    amc::StringTag stringTag;
    EXPECT_EQ(amc::TagType::String, stringTag.getType());
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

    amc::StringTag stringTag("stringTest", "HELLO WORLD THIS IS A TEST STRING!");
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
    amc::StringTag stringTag;
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
    amc::StringTag stringTag;
    EXPECT_STREQ("", stringTag.getValue().c_str());
    stringTag.setValue(value);
    EXPECT_STREQ(value.c_str(), stringTag.getValue().c_str());
    stringTag.setValue(value2);
    EXPECT_STREQ(value2.c_str(), stringTag.getValue().c_str());
}

TEST(StringTag, tag_cast)
{
    amc::AbstractTag *testTag = new amc::StringTag("A", "ABC");

    amc::StringTag *otherTag = tag_cast<amc::StringTag*>(testTag);
    EXPECT_EQ(otherTag, testTag);

    amc::IntTag *nullTag = tag_cast<amc::IntTag*>(testTag);
    EXPECT_EQ(nullTag, nullptr);

    delete testTag;
}