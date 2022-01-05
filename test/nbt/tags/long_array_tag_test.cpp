// AwesomeMC
#include <AwesomeMC/nbt/tags/long_array_tag.hpp>
#include <AwesomeMC/nbt/tags/end_tag.hpp>
#include <AwesomeMC/nbt/tags/int_tag.hpp>
#include <AwesomeMC/util/byte_swap.hpp>

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(LongArrayTag, Constructor)
{
    nbt::LongArrayTag longArrayTag;
    EXPECT_STREQ("", longArrayTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::LongArray, longArrayTag.getType());
    std::vector<int64_t> data = longArrayTag.getValue();
    EXPECT_EQ(0, data.size());
}

TEST(LongArrayTag, Constructor_2)
{
    nbt::LongArrayTag longArrayTag("TagName");
    EXPECT_STREQ("TagName", longArrayTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::LongArray, longArrayTag.getType());
    std::vector<int64_t> data = longArrayTag.getValue();
    EXPECT_EQ(0, data.size());
}

TEST(LongArrayTag, Constructor_3)
{
    std::vector<int64_t> value = {-123, 0, 127};
    nbt::LongArrayTag longArrayTag(value);
    EXPECT_STREQ("", longArrayTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::LongArray, longArrayTag.getType());
    std::vector<int64_t> data = longArrayTag.getValue();
    EXPECT_EQ(3, data.size());
    EXPECT_EQ(value[0], data[0]);
    EXPECT_EQ(value[1], data[1]);
    EXPECT_EQ(value[2], data[2]);
}

TEST(LongArrayTag, Constructor_4)
{
    std::vector<int64_t> value = {-123, 0, 127};
    nbt::LongArrayTag longArrayTag("TagName", value);
    EXPECT_STREQ("TagName", longArrayTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::LongArray, longArrayTag.getType());
    std::vector<int64_t> data = longArrayTag.getValue();
    EXPECT_EQ(3, data.size());
    EXPECT_EQ(value[0], data[0]);
    EXPECT_EQ(value[1], data[1]);
    EXPECT_EQ(value[2], data[2]);
}

TEST(LongArrayTag, CopyConstructor)
{
    std::string name = "CopyConstructor";
    std::vector<int64_t> value = {-0x7123FFFFFFFFFFFF, 0, 0x7FFFFFFFFFFFFF23};

    // Init
    nbt::LongArrayTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_THAT(tagA.getValue(), testing::ElementsAreArray(value.begin(), value.end()));

    // Test Copy
    nbt::LongArrayTag tagB(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_THAT(tagB.getValue(), testing::ElementsAreArray(tagA.getValue().begin(), tagA.getValue().end()));
}

TEST(LongArrayTag, MoveConstructor)
{
    std::string name = "MoveConstructor";
    std::vector<int64_t> value = {-0x7123FFFFFFFFFFFF, -5, -1, 0, 1, 2, 3, 5, 0x7FFFFFFFFFFFFF23};

    // Init
    nbt::LongArrayTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_THAT(tagA.getValue(), testing::ElementsAreArray(value.begin(), value.end()));

    // Test Move
    nbt::LongArrayTag tagB(std::move(tagA));
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_THAT(tagB.getValue(), testing::ElementsAreArray(value.begin(), value.end()));
}

TEST(LongArrayTag, CopyAssignment)
{
    std::string name = "CopyAssignment";
    std::vector<int64_t> value = {0x7123FFFFFFFFFFFF, -50, -10, 0, 10, 20, 30, 50, 0x7FFFFFFFFFFFFF23};

    // Init A
    nbt::LongArrayTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_THAT(tagA.getValue(), testing::ElementsAreArray(value.begin(), value.end()));

    // Init B
    nbt::LongArrayTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_EQ(tagB.getValue().size(), 0);

    // Test Copy Assignment
    tagB = tagA;
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_THAT(tagB.getValue(), testing::ElementsAreArray(tagA.getValue().begin(), tagA.getValue().end()));
}

TEST(LongArrayTag, MoveAssignment)
{
    std::string name = "MoveAssignment";
    std::vector<int64_t> value = {-0x7123FFFFFFFFFFFF, -33, -11, 0, 11, 22, 33, 55, 0x7FFFFFFFFFFFFF23};

    // Init A
    nbt::LongArrayTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_THAT(tagA.getValue(), testing::ElementsAreArray(value.begin(), value.end()));

    // Init B
    nbt::LongArrayTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_EQ(tagB.getValue().size(), 0);

    // Test Move Assignment
    tagB = std::move(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_THAT(tagB.getValue(), testing::ElementsAreArray(value.begin(), value.end()));
}

TEST(LongArrayTag, clone)
{
    nbt::LongArrayTag longArrayTagA("Test1", {1, 2, 3});

    nbt::LongArrayTag *longArrayTagB = tag_cast<nbt::LongArrayTag*>(longArrayTagA.clone());
    EXPECT_TRUE(longArrayTagA == *longArrayTagB);
}

TEST(LongArrayTag, Equal)
{
    nbt::LongArrayTag longArrayTagA("Test1", {1, 2, 3});
    nbt::LongArrayTag longArrayTagB("Test1", {1, 2, 3});
    nbt::LongArrayTag longArrayTagC("Test1", {1, 2, 3});
    nbt::LongArrayTag longArrayTagD("Test2", {1, 2, 5});
    nbt::LongArrayTag longArrayTagE;
    nbt::EndTag endTag;

    EXPECT_TRUE(longArrayTagA == longArrayTagA);  // Test same object
    EXPECT_TRUE(longArrayTagA == longArrayTagB);  // Test same data #1
    EXPECT_TRUE(longArrayTagA == longArrayTagC);  // Test same data #2
    longArrayTagB.setValue({1, 2, 5});
    EXPECT_FALSE(longArrayTagA == longArrayTagB); // Test different data #1
    longArrayTagC.setName("Test3");
    EXPECT_FALSE(longArrayTagA == longArrayTagC); // Test different data #2

    EXPECT_FALSE(longArrayTagE == endTag);   // Test different types
}

TEST(LongArrayTag, NotEqual)
{
    nbt::LongArrayTag longArrayTagA("Test1", {1, 2, 3});
    nbt::LongArrayTag longArrayTagB("Test1", {1, 2, 3});
    nbt::LongArrayTag longArrayTagC("Test1", {1, 2, 3});
    nbt::LongArrayTag longArrayTagD("Test2", {1, 2, 5});
    nbt::LongArrayTag longArrayTagE;
    nbt::EndTag endTag;

    EXPECT_FALSE(longArrayTagA != longArrayTagA);  // Test same object
    EXPECT_FALSE(longArrayTagA != longArrayTagB);  // Test same data #1
    EXPECT_FALSE(longArrayTagA != longArrayTagC);  // Test same data #2
    longArrayTagB.setValue({1, 2, 5});
    EXPECT_TRUE(longArrayTagA != longArrayTagB); // Test different data #1
    longArrayTagC.setName("Test3");
    EXPECT_TRUE(longArrayTagA != longArrayTagC); // Test different data #2

    EXPECT_TRUE(longArrayTagE != endTag);   // Test different types
}

TEST(LongArrayTag, getType)
{
    nbt::LongArrayTag longArrayTag;
    EXPECT_EQ(nbt::TagType::LongArray, longArrayTag.getType());
}

TEST(LongArrayTag, getData)
{
    const std::vector<unsigned char> testData = {
        0x0C, 0x00, 0x0C, 0x6C, 0x6F, 0x6E, 0x67, 0x41,
        0x72, 0x72, 0x61, 0x79, 0x54, 0x61, 0x67, 0x00,
        0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xF0, 0xBD, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x07,
        0x5B, 0xCD, 0x15
    };

    nbt::LongArrayTag longArrayTag("longArrayTag", std::vector<int64_t>({-1000001, 4, 123456789}));
    std::vector<unsigned char> data = longArrayTag.getData(false);

    EXPECT_EQ(data.size(), testData.size());
    EXPECT_THAT(data, ::testing::ElementsAreArray(testData));

    std::vector<unsigned char> data2 = longArrayTag.getData(true);
    EXPECT_EQ(28, data2.size());
    EXPECT_THAT(data2, ::testing::ElementsAreArray(testData.begin() + 15, testData.end()));
}

TEST(LongArrayTag, isEmpty)
{
    nbt::LongArrayTag longArrayTagA;
    EXPECT_TRUE(longArrayTagA.isEmpty());
    longArrayTagA.pushBack(2);
    EXPECT_FALSE(longArrayTagA.isEmpty());

    nbt::LongArrayTag longArrayTagB("TestTag", {1, 2, 3});
    EXPECT_FALSE(longArrayTagB.isEmpty());
}

TEST(LongArrayTag, clear)
{
    nbt::LongArrayTag longArrayTagB("TestTag", {1, 2, 3});
    EXPECT_FALSE(longArrayTagB.isEmpty());
    longArrayTagB.clear();
    EXPECT_TRUE(longArrayTagB.isEmpty());
}

TEST(LongArrayTag, erase)
{
    nbt::LongArrayTag longArrayTagA("TestTag", {1, 2, 3});
    // Test index too high
    EXPECT_FALSE(longArrayTagA.erase(3));
    EXPECT_FALSE(longArrayTagA.erase(900));

    // successively erase first index until empty
    ASSERT_FALSE(longArrayTagA.isEmpty());
    EXPECT_TRUE(longArrayTagA.erase(0));
    EXPECT_TRUE(longArrayTagA.erase(0));
    EXPECT_TRUE(longArrayTagA.erase(0));
    ASSERT_TRUE(longArrayTagA.isEmpty());

    // Expect false, when trying to erase from empty ByteAraryTag
    EXPECT_FALSE(longArrayTagA.erase(0));

    // Erase from middle
    nbt::LongArrayTag longArrayTagB("TestTag", {1, 2, 3});
    ASSERT_EQ(3, longArrayTagB.size());
    std::vector<int64_t> data1 = longArrayTagB.getValue();
    EXPECT_THAT(data1, testing::ElementsAre(1, 2, 3));
    longArrayTagB.erase(1);
    std::vector<int64_t> data2 = longArrayTagB.getValue();
    ASSERT_EQ(2, longArrayTagB.size());
    EXPECT_THAT(data2, testing::ElementsAre(1, 3));

}

TEST(LongArrayTag, insert)
{
    // Insert into empty
    nbt::LongArrayTag longArrayTagA;
    // Test invalid index
    ASSERT_EQ(0, longArrayTagA.size());
    EXPECT_FALSE(longArrayTagA.insert(1, 1));
    ASSERT_EQ(0, longArrayTagA.size());

    // Test valid index - insert at end
    EXPECT_TRUE(longArrayTagA.insert(0, 1));
    EXPECT_EQ(1, longArrayTagA.size());

    // Insert in the middle
    nbt::LongArrayTag longArrayTagB("TestTag", {1, 3});
    ASSERT_EQ(2, longArrayTagB.size());
    EXPECT_TRUE(longArrayTagB.insert(1, 2));
    EXPECT_EQ(3, longArrayTagB.size());
    std::vector<int64_t> data1 = longArrayTagB.getValue();
    EXPECT_THAT(data1, testing::ElementsAre(1, 2, 3));
}

TEST(LongArrayTag, pushBack)
{
    nbt::LongArrayTag longArrayTagA;
    EXPECT_EQ(0, longArrayTagA.size());
    longArrayTagA.pushBack(1);
    EXPECT_EQ(1, longArrayTagA.at(0));
    EXPECT_EQ(1, longArrayTagA.size());
    longArrayTagA.pushBack(100);
    EXPECT_EQ(100, longArrayTagA.at(1));
    EXPECT_EQ(2, longArrayTagA.size());
}

TEST(LongArrayTag, size)
{
    nbt::LongArrayTag longArrayTagA;
    EXPECT_EQ(0, longArrayTagA.size());

    nbt::LongArrayTag longArrayTagB("TestTag", {1, 2, 3});
    EXPECT_EQ(3, longArrayTagB.size());

    longArrayTagB.clear();
    EXPECT_EQ(0, longArrayTagB.size());
}

TEST(LongArrayTag, at)
{
    const int64_t value1_in = -115;
    const int64_t value2_in = 0;
    const int64_t value3_in = 98;
    int64_t value1_out = 0;
    int64_t value2_out = 0;
    int64_t value3_out = 0;

    // Test copy
    nbt::LongArrayTag longArrayTagA("TestTag", {value1_in, value2_in, value3_in});
    ASSERT_EQ(3, longArrayTagA.size());
    value1_out = longArrayTagA.at(0);
    EXPECT_EQ(value1_out, value1_in);
    value2_out = longArrayTagA.at(1);
    EXPECT_EQ(value2_out, value2_in);
    value3_out = longArrayTagA.at(2);
    EXPECT_EQ(value3_out, value3_in);

    // Test reference
    nbt::LongArrayTag longArrayTagB("TestTag", {value1_in});
    ASSERT_EQ(1, longArrayTagB.size());
    int64_t &value1_out_ref = longArrayTagA.at(0);
    EXPECT_EQ(value1_out_ref, value1_in);
    value1_out_ref = value2_in;
    value1_out = longArrayTagA.at(0);
    EXPECT_EQ(value1_out, value2_in);
}

TEST(LongArrayTag, at_const)
{
    const int64_t value1_in = -115;
    const int64_t value2_in = 0;
    const int64_t value3_in = 98;

    // Test const copy
    const nbt::LongArrayTag longArrayTagA("TestTag", {value1_in, value2_in, value3_in});
    ASSERT_EQ(3, longArrayTagA.size());
    const int64_t value1_out = longArrayTagA.at(0);
    EXPECT_EQ(value1_out, value1_in);
    const int64_t value2_out = longArrayTagA.at(1);
    EXPECT_EQ(value2_out, value2_in);
    const int64_t value3_out = longArrayTagA.at(2);
    EXPECT_EQ(value3_out, value3_in);
}

TEST(LongArrayTag, getValue)
{
    std::vector<int64_t> value = {1, 2, 3, 4};
    std::vector<int64_t> value2 = {1, 2, 3, 5};
    nbt::LongArrayTag longArrayTag;

    std::vector<int64_t> data = longArrayTag.getValue();
    EXPECT_EQ(0, data.size());
    longArrayTag.setValue(value);
    std::vector<int64_t> data2 = longArrayTag.getValue();
    ASSERT_THAT(data2, testing::ElementsAre(1, 2, 3, 4));
    longArrayTag.setValue(value2);
    std::vector<int64_t> data3 = longArrayTag.getValue();
    ASSERT_THAT(data3, testing::ElementsAre(1, 2, 3, 5));
}

TEST(LongArrayTag, setValue)
{
    std::vector<int64_t> value = {1, 2, 3, 4};
    nbt::LongArrayTag longArrayTag;
    EXPECT_EQ(0, longArrayTag.size());
    longArrayTag.setValue(value);
    EXPECT_EQ(4, longArrayTag.size());
    std::vector<int64_t> data2 = longArrayTag.getValue();
    ASSERT_THAT(data2, testing::ElementsAre(1, 2, 3, 4));
}

TEST(LongArrayTag, tag_cast)
{
    nbt::AbstractTag *testTag = new nbt::LongArrayTag("A", std::vector<int64_t>({1, 2, 3}));

    nbt::LongArrayTag *otherTag = tag_cast<nbt::LongArrayTag*>(testTag);
    EXPECT_EQ(otherTag, testTag);

    nbt::IntTag *nullTag = tag_cast<nbt::IntTag*>(testTag);
    EXPECT_EQ(nullTag, nullptr);
}