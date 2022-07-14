// AwesomeMC
#include <AwesomeMC/nbt/tags/int_array_tag.hpp>
#include <AwesomeMC/nbt/tags/end_tag.hpp>
#include <AwesomeMC/nbt/tags/int_tag.hpp>

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// STL
#include <type_traits>

TEST(IntArrayTag, value_type)
{
    bool check = std::is_same<int32_t, amc::IntArrayTag::value_type>::value;
    EXPECT_TRUE(check);
}

TEST(IntArrayTag, Constructor)
{
    amc::IntArrayTag intArrayTag;
    EXPECT_STREQ("", intArrayTag.getName().c_str());
    EXPECT_EQ(amc::TagType::IntArray, intArrayTag.getType());
    std::vector<int32_t> data = intArrayTag.getValue();
    EXPECT_EQ(0, data.size());
}

TEST(IntArrayTag, Constructor_2)
{
    amc::IntArrayTag intArrayTag("TagName");
    EXPECT_STREQ("TagName", intArrayTag.getName().c_str());
    EXPECT_EQ(amc::TagType::IntArray, intArrayTag.getType());
    std::vector<int32_t> data = intArrayTag.getValue();
    EXPECT_EQ(0, data.size());
}

TEST(IntArrayTag, Constructor_3)
{
    std::vector<int32_t> value = {-123, 0, 127};
    amc::IntArrayTag intArrayTag(value);
    EXPECT_STREQ("", intArrayTag.getName().c_str());
    EXPECT_EQ(amc::TagType::IntArray, intArrayTag.getType());
    std::vector<int32_t> data = intArrayTag.getValue();
    EXPECT_EQ(3, data.size());
    EXPECT_EQ(value[0], data[0]);
    EXPECT_EQ(value[1], data[1]);
    EXPECT_EQ(value[2], data[2]);
}

TEST(IntArrayTag, Constructor_4)
{
    std::vector<int32_t> value = {-123, 0, 127};
    amc::IntArrayTag intArrayTag("TagName", value);
    EXPECT_STREQ("TagName", intArrayTag.getName().c_str());
    EXPECT_EQ(amc::TagType::IntArray, intArrayTag.getType());
    std::vector<int32_t> data = intArrayTag.getValue();
    EXPECT_EQ(3, data.size());
    EXPECT_EQ(value[0], data[0]);
    EXPECT_EQ(value[1], data[1]);
    EXPECT_EQ(value[2], data[2]);
}

TEST(IntArrayTag, CopyConstructor)
{
    std::string name = "CopyConstructor";
    std::vector<int32_t> value = {-0x7123FFFF, 0, 0x7FFFFF23};

    // Init
    amc::IntArrayTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_THAT(tagA.getValue(), testing::ElementsAreArray(value.begin(), value.end()));

    // Test Copy
    amc::IntArrayTag tagB(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_THAT(tagB.getValue(), testing::ElementsAreArray(tagA.getValue().begin(), tagA.getValue().end()));
}

TEST(IntArrayTag, MoveConstructor)
{
    std::string name = "MoveConstructor";
    std::vector<int32_t> value = {-0x7123FFFF, -5, -1, 0, 1, 2, 3, 5, 0x7FFFFF23};

    // Init
    amc::IntArrayTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_THAT(tagA.getValue(), testing::ElementsAreArray(value.begin(), value.end()));

    // Test Move
    amc::IntArrayTag tagB(std::move(tagA));
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_THAT(tagB.getValue(), testing::ElementsAreArray(value.begin(), value.end()));
}

TEST(IntArrayTag, CopyAssignment)
{
    std::string name = "CopyAssignment";
    std::vector<int32_t> value = {0x7FFFFFFF, -50, -10, 0, 10, 20, 30, 50, 0x7FFFFFFF};

    // Init A
    amc::IntArrayTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_THAT(tagA.getValue(), testing::ElementsAreArray(value.begin(), value.end()));

    // Init B
    amc::IntArrayTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_EQ(tagB.getValue().size(), 0);

    // Test Copy Assignment
    tagB = tagA;
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_THAT(tagB.getValue(), testing::ElementsAreArray(tagA.getValue().begin(), tagA.getValue().end()));
}

TEST(IntArrayTag, MoveAssignment)
{
    std::string name = "MoveAssignment";
    std::vector<int32_t> value = {-0x7FFFFFFF, -33, -11, 0, 11, 22, 33, 55, 0x7FFFFFFF};

    // Init A
    amc::IntArrayTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_THAT(tagA.getValue(), testing::ElementsAreArray(value.begin(), value.end()));

    // Init B
    amc::IntArrayTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_EQ(tagB.getValue().size(), 0);

    // Test Move Assignment
    tagB = std::move(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_THAT(tagB.getValue(), testing::ElementsAreArray(value.begin(), value.end()));
}

TEST(IntArrayTag, clone)
{
    amc::IntArrayTag intArrayTagA("Test1", {1, 2, 3});

    amc::IntArrayTag *intArrayTagB = tag_cast<amc::IntArrayTag*>(intArrayTagA.clone());
    EXPECT_TRUE(intArrayTagA == *intArrayTagB);

    delete intArrayTagB;
}

TEST(IntArrayTag, Equal)
{
    amc::IntArrayTag intArrayTagA("Test1", {1, 2, 3});
    amc::IntArrayTag intArrayTagB("Test1", {1, 2, 3});
    amc::IntArrayTag intArrayTagC("Test1", {1, 2, 3});
    amc::IntArrayTag intArrayTagD("Test2", {1, 2, 5});
    amc::IntArrayTag intArrayTagE;
    amc::EndTag endTag;

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
    amc::IntArrayTag intArrayTagA("Test1", {1, 2, 3});
    amc::IntArrayTag intArrayTagB("Test1", {1, 2, 3});
    amc::IntArrayTag intArrayTagC("Test1", {1, 2, 3});
    amc::IntArrayTag intArrayTagD("Test2", {1, 2, 5});
    amc::IntArrayTag intArrayTagE;
    amc::EndTag endTag;

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
    amc::IntArrayTag intArrayTag;
    EXPECT_EQ(amc::TagType::IntArray, intArrayTag.getType());
}

TEST(IntArrayTag, getData)
{
    const std::vector<unsigned char> testData = {
        0x0B, 0x00, 0x0B, 0x69, 0x6E, 0x74, 0x41, 0x72, 
        0x72, 0x61, 0x79, 0x54, 0x61, 0x67, 0x00, 0x00, 
        0x00, 0x03, 0xFF, 0xFF, 0xEE, 0x29, 0x00, 0x00,
        0x00, 0x0C, 0x00, 0x00, 0xB2, 0xDD
    };

    amc::IntArrayTag intArrayTag("intArrayTag", std::vector<int32_t>({-4567, 12, 45789}));
    std::vector<unsigned char> data = intArrayTag.getData(false);

    EXPECT_EQ(data.size(), testData.size());
    EXPECT_THAT(data, ::testing::ElementsAreArray(testData));

    std::vector<unsigned char> data2 = intArrayTag.getData(true);
    EXPECT_EQ(16, data2.size());
    EXPECT_THAT(data2, ::testing::ElementsAreArray(testData.begin() + 14, testData.end()));
}

TEST(IntArrayTag, isEmpty)
{
    amc::IntArrayTag intArrayTagA;
    EXPECT_TRUE(intArrayTagA.isEmpty());
    intArrayTagA.pushBack(2);
    EXPECT_FALSE(intArrayTagA.isEmpty());

    amc::IntArrayTag intArrayTagB("TestTag", {1, 2, 3});
    EXPECT_FALSE(intArrayTagB.isEmpty());
}

TEST(IntArrayTag, clear)
{
    amc::IntArrayTag intArrayTagB("TestTag", {1, 2, 3});
    EXPECT_FALSE(intArrayTagB.isEmpty());
    intArrayTagB.clear();
    EXPECT_TRUE(intArrayTagB.isEmpty());
}

TEST(IntArrayTag, erase)
{
    amc::IntArrayTag intArrayTagA("TestTag", {1, 2, 3});
    // Test index too high
    EXPECT_FALSE(intArrayTagA.eraseAt(3));
    EXPECT_FALSE(intArrayTagA.eraseAt(900));

    // successively erase first index until empty
    ASSERT_FALSE(intArrayTagA.isEmpty());
    EXPECT_TRUE(intArrayTagA.eraseAt(0));
    EXPECT_TRUE(intArrayTagA.eraseAt(0));
    EXPECT_TRUE(intArrayTagA.eraseAt(0));
    ASSERT_TRUE(intArrayTagA.isEmpty());

    // Expect false, when trying to erase from empty ByteAraryTag
    EXPECT_FALSE(intArrayTagA.eraseAt(0));

    // Erase from middle
    amc::IntArrayTag intArrayTagB("TestTag", {1, 2, 3});
    ASSERT_EQ(3, intArrayTagB.size());
    std::vector<int32_t> data1 = intArrayTagB.getValue();
    EXPECT_THAT(data1, testing::ElementsAre(1, 2, 3));
    intArrayTagB.eraseAt(1);
    std::vector<int32_t> data2 = intArrayTagB.getValue();
    ASSERT_EQ(2, intArrayTagB.size());
    EXPECT_THAT(data2, testing::ElementsAre(1, 3));

}

TEST(IntArrayTag, insert)
{
    // Insert into empty
    amc::IntArrayTag intArrayTagA;
    // Test invalid index
    ASSERT_EQ(0, intArrayTagA.size());
    EXPECT_FALSE(intArrayTagA.insert(1, 1));
    ASSERT_EQ(0, intArrayTagA.size());

    // Test valid index - insert at end
    EXPECT_TRUE(intArrayTagA.insert(0, 1));
    EXPECT_EQ(1, intArrayTagA.size());

    // Insert in the middle
    amc::IntArrayTag intArrayTagB("TestTag", {1, 3});
    ASSERT_EQ(2, intArrayTagB.size());
    EXPECT_TRUE(intArrayTagB.insert(1, 2));
    EXPECT_EQ(3, intArrayTagB.size());
    std::vector<int32_t> data1 = intArrayTagB.getValue();
    EXPECT_THAT(data1, testing::ElementsAre(1, 2, 3));
}

TEST(IntArrayTag, pushBack)
{
    amc::IntArrayTag intArrayTagA;
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
    amc::IntArrayTag intArrayTagA;
    EXPECT_EQ(0, intArrayTagA.size());

    amc::IntArrayTag intArrayTagB("TestTag", {1, 2, 3});
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
    amc::IntArrayTag intArrayTagA("TestTag", {value1_in, value2_in, value3_in});
    ASSERT_EQ(3, intArrayTagA.size());
    value1_out = intArrayTagA.at(0);
    EXPECT_EQ(value1_out, value1_in);
    value2_out = intArrayTagA.at(1);
    EXPECT_EQ(value2_out, value2_in);
    value3_out = intArrayTagA.at(2);
    EXPECT_EQ(value3_out, value3_in);

    // Test reference
    amc::IntArrayTag intArrayTagB("TestTag", {value1_in});
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
    const amc::IntArrayTag intArrayTagA("TestTag", {value1_in, value2_in, value3_in});
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
    amc::IntArrayTag intArrayTag;

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
    amc::IntArrayTag intArrayTag;
    EXPECT_EQ(0, intArrayTag.size());
    intArrayTag.setValue(value);
    EXPECT_EQ(4, intArrayTag.size());
    std::vector<int32_t> data2 = intArrayTag.getValue();
    ASSERT_THAT(data2, testing::ElementsAre(1, 2, 3, 4));
}

TEST(IntArrayTag, tag_cast)
{
    amc::AbstractTag *testTag = new amc::IntArrayTag("A", std::vector<int32_t>({1, 2, 3}));

    amc::IntArrayTag *otherTag = tag_cast<amc::IntArrayTag*>(testTag);
    EXPECT_EQ(otherTag, testTag);

    amc::IntTag *nullTag = tag_cast<amc::IntTag*>(testTag);
    EXPECT_EQ(nullTag, nullptr);

    delete testTag;
}