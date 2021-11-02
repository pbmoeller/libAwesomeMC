#include "nbt/tags/int_array_tag.hpp"
#include "nbt/tags/end_tag.hpp"

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(IntArrayTag, Constructor)
{
    nbt::IntArrayTag intArrayTag;
    EXPECT_STREQ("", intArrayTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::IntArray, intArrayTag.getType());
    std::vector<int32_t> data = intArrayTag.getValue();
    EXPECT_EQ(0, data.size());
}

TEST(IntArrayTag, Constructor_2)
{
    nbt::IntArrayTag intArrayTag("TagName");
    EXPECT_STREQ("TagName", intArrayTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::IntArray, intArrayTag.getType());
    std::vector<int32_t> data = intArrayTag.getValue();
    EXPECT_EQ(0, data.size());
}

TEST(IntArrayTag, Constructor_3)
{
    std::vector<int32_t> value = {-123, 0, 127};
    nbt::IntArrayTag intArrayTag(value);
    EXPECT_STREQ("", intArrayTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::IntArray, intArrayTag.getType());
    std::vector<int32_t> data = intArrayTag.getValue();
    EXPECT_EQ(3, data.size());
    EXPECT_EQ(value[0], data[0]);
    EXPECT_EQ(value[1], data[1]);
    EXPECT_EQ(value[2], data[2]);
}

TEST(IntArrayTag, Constructor_4)
{
    std::vector<int32_t> value = {-123, 0, 127};
    nbt::IntArrayTag intArrayTag("TagName", value);
    EXPECT_STREQ("TagName", intArrayTag.getName().c_str());
    EXPECT_EQ(nbt::TagType::IntArray, intArrayTag.getType());
    std::vector<int32_t> data = intArrayTag.getValue();
    EXPECT_EQ(3, data.size());
    EXPECT_EQ(value[0], data[0]);
    EXPECT_EQ(value[1], data[1]);
    EXPECT_EQ(value[2], data[2]);
}

TEST(IntArrayTag, CopyConstructor)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(IntArrayTag, MoveConstructor)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(IntArrayTag, CopyAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(IntArrayTag, MoveAssignment)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(IntArrayTag, clone)
{
    nbt::IntArrayTag intArrayTagA("Test1", {1, 2, 3});

    nbt::IntArrayTag *intArrayTagB = (nbt::IntArrayTag *)intArrayTagA.clone();
    EXPECT_TRUE(intArrayTagA == *intArrayTagB);
}

TEST(IntArrayTag, Equal)
{
    nbt::IntArrayTag intArrayTagA("Test1", {1, 2, 3});
    nbt::IntArrayTag intArrayTagB("Test1", {1, 2, 3});
    nbt::IntArrayTag intArrayTagC("Test1", {1, 2, 3});
    nbt::IntArrayTag intArrayTagD("Test2", {1, 2, 5});
    nbt::IntArrayTag intArrayTagE;
    nbt::EndTag endTag;

    EXPECT_TRUE(intArrayTagA == intArrayTagA);  // Test same object
    EXPECT_TRUE(intArrayTagA == intArrayTagB);  // Test same data #1
    EXPECT_TRUE(intArrayTagA == intArrayTagC);  // Test same data #2
    intArrayTagB.setValue({1, 2, 5});
    EXPECT_FALSE(intArrayTagA == intArrayTagB); // Test different data #1
    intArrayTagC.setName("Test3");
    EXPECT_FALSE(intArrayTagA == intArrayTagC); // Test different data #2

    EXPECT_FALSE(intArrayTagE == endTag);   // Test different types
}

TEST(IntArrayTag, NotEqual)
{
    nbt::IntArrayTag intArrayTagA("Test1", {1, 2, 3});
    nbt::IntArrayTag intArrayTagB("Test1", {1, 2, 3});
    nbt::IntArrayTag intArrayTagC("Test1", {1, 2, 3});
    nbt::IntArrayTag intArrayTagD("Test2", {1, 2, 5});
    nbt::IntArrayTag intArrayTagE;
    nbt::EndTag endTag;

    EXPECT_FALSE(intArrayTagA != intArrayTagA);  // Test same object
    EXPECT_FALSE(intArrayTagA != intArrayTagB);  // Test same data #1
    EXPECT_FALSE(intArrayTagA != intArrayTagC);  // Test same data #2
    intArrayTagB.setValue({1, 2, 5});
    EXPECT_TRUE(intArrayTagA != intArrayTagB); // Test different data #1
    intArrayTagC.setName("Test3");
    EXPECT_TRUE(intArrayTagA != intArrayTagC); // Test different data #2

    EXPECT_TRUE(intArrayTagE != endTag);   // Test different types
}

TEST(IntArrayTag, getType)
{
    nbt::IntArrayTag intArrayTag;
    EXPECT_EQ(nbt::TagType::IntArray, intArrayTag.getType());
}

TEST(IntArrayTag, getData)
{
    GTEST_SKIP() << "<<<  Test not implemented  >>>";
}

TEST(IntArrayTag, isEmpty)
{
    nbt::IntArrayTag intArrayTagA;
    EXPECT_TRUE(intArrayTagA.isEmpty());
    intArrayTagA.pushBack(2);
    EXPECT_FALSE(intArrayTagA.isEmpty());

    nbt::IntArrayTag intArrayTagB("TestTag", {1, 2, 3});
    EXPECT_FALSE(intArrayTagB.isEmpty());
}

TEST(IntArrayTag, clear)
{
    nbt::IntArrayTag intArrayTagB("TestTag", {1, 2, 3});
    EXPECT_FALSE(intArrayTagB.isEmpty());
    intArrayTagB.clear();
    EXPECT_TRUE(intArrayTagB.isEmpty());
}

TEST(IntArrayTag, erase)
{
    nbt::IntArrayTag intArrayTagA("TestTag", {1, 2, 3});
    // Test index too high
    EXPECT_FALSE(intArrayTagA.erase(3));
    EXPECT_FALSE(intArrayTagA.erase(900));

    // successively erase first index until empty
    ASSERT_FALSE(intArrayTagA.isEmpty());
    EXPECT_TRUE(intArrayTagA.erase(0));
    EXPECT_TRUE(intArrayTagA.erase(0));
    EXPECT_TRUE(intArrayTagA.erase(0));
    ASSERT_TRUE(intArrayTagA.isEmpty());

    // Expect false, when trying to erase from empty ByteAraryTag
    EXPECT_FALSE(intArrayTagA.erase(0));

    // Erase from middle
    nbt::IntArrayTag intArrayTagB("TestTag", {1, 2, 3});
    ASSERT_EQ(3, intArrayTagB.size());
    std::vector<int32_t> data1 = intArrayTagB.getValue();
    EXPECT_THAT(data1, testing::ElementsAre(1, 2, 3));
    intArrayTagB.erase(1);
    std::vector<int32_t> data2 = intArrayTagB.getValue();
    ASSERT_EQ(2, intArrayTagB.size());
    EXPECT_THAT(data2, testing::ElementsAre(1, 3));

}

TEST(IntArrayTag, insert)
{
    // Insert into empty
    nbt::IntArrayTag intArrayTagA;
    // Test invalid index
    ASSERT_EQ(0, intArrayTagA.size());
    EXPECT_FALSE(intArrayTagA.insert(1, 1));
    ASSERT_EQ(0, intArrayTagA.size());

    // Test valid index - insert at end
    EXPECT_TRUE(intArrayTagA.insert(0, 1));
    EXPECT_EQ(1, intArrayTagA.size());

    // Insert in the middle
    nbt::IntArrayTag intArrayTagB("TestTag", {1, 3});
    ASSERT_EQ(2, intArrayTagB.size());
    EXPECT_TRUE(intArrayTagB.insert(1, 2));
    EXPECT_EQ(3, intArrayTagB.size());
    std::vector<int32_t> data1 = intArrayTagB.getValue();
    EXPECT_THAT(data1, testing::ElementsAre(1, 2, 3));
}

TEST(IntArrayTag, pushBack)
{
    nbt::IntArrayTag intArrayTagA;
    EXPECT_EQ(0, intArrayTagA.size());
    intArrayTagA.pushBack(1);
    EXPECT_EQ(1, intArrayTagA.at(0));
    EXPECT_EQ(1, intArrayTagA.size());
    intArrayTagA.pushBack(100);
    EXPECT_EQ(100, intArrayTagA.at(1));
    EXPECT_EQ(2, intArrayTagA.size());
}

TEST(IntArrayTag, size)
{
    nbt::IntArrayTag intArrayTagA;
    EXPECT_EQ(0, intArrayTagA.size());

    nbt::IntArrayTag intArrayTagB("TestTag", {1, 2, 3});
    EXPECT_EQ(3, intArrayTagB.size());

    intArrayTagB.clear();
    EXPECT_EQ(0, intArrayTagB.size());
}

TEST(IntArrayTag, at)
{
    const int32_t value1_in = -115;
    const int32_t value2_in = 0;
    const int32_t value3_in = 98;
    int32_t value1_out = 0;
    int32_t value2_out = 0;
    int32_t value3_out = 0;

    // Test copy
    nbt::IntArrayTag intArrayTagA("TestTag", {value1_in, value2_in, value3_in});
    ASSERT_EQ(3, intArrayTagA.size());
    value1_out = intArrayTagA.at(0);
    EXPECT_EQ(value1_out, value1_in);
    value2_out = intArrayTagA.at(1);
    EXPECT_EQ(value2_out, value2_in);
    value3_out = intArrayTagA.at(2);
    EXPECT_EQ(value3_out, value3_in);

    // Test reference
    nbt::IntArrayTag intArrayTagB("TestTag", {value1_in});
    ASSERT_EQ(1, intArrayTagB.size());
    int32_t &value1_out_ref = intArrayTagA.at(0);
    EXPECT_EQ(value1_out_ref, value1_in);
    value1_out_ref = value2_in;
    value1_out = intArrayTagA.at(0);
    EXPECT_EQ(value1_out, value2_in);
}

TEST(IntArrayTag, at_const)
{
    const int32_t value1_in = -115;
    const int32_t value2_in = 0;
    const int32_t value3_in = 98;

    // Test const copy
    const nbt::IntArrayTag intArrayTagA("TestTag", {value1_in, value2_in, value3_in});
    ASSERT_EQ(3, intArrayTagA.size());
    const int32_t value1_out = intArrayTagA.at(0);
    EXPECT_EQ(value1_out, value1_in);
    const int32_t value2_out = intArrayTagA.at(1);
    EXPECT_EQ(value2_out, value2_in);
    const int32_t value3_out = intArrayTagA.at(2);
    EXPECT_EQ(value3_out, value3_in);
}

TEST(IntArrayTag, getValue)
{
    std::vector<int32_t> value = {1, 2, 3, 4};
    std::vector<int32_t> value2 = {1, 2, 3, 5};
    nbt::IntArrayTag intArrayTag;

    std::vector<int32_t> data = intArrayTag.getValue();
    EXPECT_EQ(0, data.size());
    intArrayTag.setValue(value);
    std::vector<int32_t> data2 = intArrayTag.getValue();
    ASSERT_THAT(data2, testing::ElementsAre(1, 2, 3, 4));
    intArrayTag.setValue(value2);
    std::vector<int32_t> data3 = intArrayTag.getValue();
    ASSERT_THAT(data3, testing::ElementsAre(1, 2, 3, 5));
}

TEST(IntArrayTag, setValue)
{
    std::vector<int32_t> value = {1, 2, 3, 4};
    nbt::IntArrayTag intArrayTag;
    EXPECT_EQ(0, intArrayTag.size());
    intArrayTag.setValue(value);
    EXPECT_EQ(4, intArrayTag.size());
    std::vector<int32_t> data2 = intArrayTag.getValue();
    ASSERT_THAT(data2, testing::ElementsAre(1, 2, 3, 4));
}