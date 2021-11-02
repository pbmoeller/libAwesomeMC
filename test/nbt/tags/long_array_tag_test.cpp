#include "nbt/tags/long_array_tag.hpp"
#include "nbt/tags/end_tag.hpp"

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
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(LongArrayTag, MoveConstructor)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(LongArrayTag, CopyAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(LongArrayTag, MoveAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(LongArrayTag, clone)
{
    nbt::LongArrayTag longArrayTagA("Test1", {1, 2, 3});

    nbt::LongArrayTag *longArrayTagB = (nbt::LongArrayTag *)longArrayTagA.clone();
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
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
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