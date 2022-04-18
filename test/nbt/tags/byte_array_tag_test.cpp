// AwesomeMC
#include <AwesomeMC/nbt/tags/byte_array_tag.hpp>
#include <AwesomeMC/nbt/tags/end_tag.hpp>
#include <AwesomeMC/nbt/tags/int_tag.hpp>

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// STL
#include <type_traits>

TEST(ByteArrayTag, value_type)
{
    bool check = std::is_same<int8_t, amc::ByteArrayTag::value_type>::value;
    EXPECT_TRUE(check);
}

TEST(ByteArrayTag, Constructor)
{
    amc::ByteArrayTag byteArrayTag;
    EXPECT_STREQ("", byteArrayTag.getName().c_str());
    EXPECT_EQ(amc::TagType::ByteArray, byteArrayTag.getType());
    std::vector<int8_t> data = byteArrayTag.getValue();
    EXPECT_EQ(0, data.size());
}

TEST(ByteArrayTag, Constructor_2)
{
    amc::ByteArrayTag byteArrayTag("TagName");
    EXPECT_STREQ("TagName", byteArrayTag.getName().c_str());
    EXPECT_EQ(amc::TagType::ByteArray, byteArrayTag.getType());
    std::vector<int8_t> data = byteArrayTag.getValue();
    EXPECT_EQ(0, data.size());
}

TEST(ByteArrayTag, Constructor_3)
{
    std::vector<int8_t> value = {-123, 0, 127};
    amc::ByteArrayTag byteArrayTag(value);
    EXPECT_STREQ("", byteArrayTag.getName().c_str());
    EXPECT_EQ(amc::TagType::ByteArray, byteArrayTag.getType());
    std::vector<int8_t> data = byteArrayTag.getValue();
    EXPECT_EQ(3, data.size());
    EXPECT_EQ(value[0], data[0]);
    EXPECT_EQ(value[1], data[1]);
    EXPECT_EQ(value[2], data[2]);
}

TEST(ByteArrayTag, Constructor_4)
{
    std::vector<int8_t> value = {-123, 0, 127};
    amc::ByteArrayTag byteArrayTag("TagName", value);
    EXPECT_STREQ("TagName", byteArrayTag.getName().c_str());
    EXPECT_EQ(amc::TagType::ByteArray, byteArrayTag.getType());
    std::vector<int8_t> data = byteArrayTag.getValue();
    EXPECT_EQ(3, data.size());
    EXPECT_EQ(value[0], data[0]);
    EXPECT_EQ(value[1], data[1]);
    EXPECT_EQ(value[2], data[2]);
}

TEST(ByteArrayTag, CopyConstructor)
{
    std::string name = "CopyConstructor";
    std::vector<int8_t> value = {-123, 0, 127};

    // Init
    amc::ByteArrayTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_THAT(tagA.getValue(), testing::ElementsAreArray(value.begin(), value.end()));

    // Test Copy
    amc::ByteArrayTag tagB(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_THAT(tagB.getValue(), testing::ElementsAreArray(tagA.getValue().begin(), tagA.getValue().end()));
}

TEST(ByteArrayTag, MoveConstructor)
{
    std::string name = "MoveConstructor";
    std::vector<int8_t> value = {-5, -1, 0, 1, 2, 3, 5};

    // Init
    amc::ByteArrayTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_THAT(tagA.getValue(), testing::ElementsAreArray(value.begin(), value.end()));

    // Test Move
    amc::ByteArrayTag tagB(std::move(tagA));
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_THAT(tagB.getValue(), testing::ElementsAreArray(value.begin(), value.end()));
}

TEST(ByteArrayTag, CopyAssignment)
{
    std::string name = "CopyAssignment";
    std::vector<int8_t> value = {-50, -10, 0, 10, 20, 30, 50};

    // Init A
    amc::ByteArrayTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_THAT(tagA.getValue(), testing::ElementsAreArray(value.begin(), value.end()));

    // Init B
    amc::ByteArrayTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_EQ(tagB.getValue().size(), 0);

    // Test Copy Assignment
    tagB = tagA;
    EXPECT_STREQ(tagB.getName().c_str(), tagA.getName().c_str());
    EXPECT_THAT(tagB.getValue(), testing::ElementsAreArray(tagA.getValue().begin(), tagA.getValue().end()));
}

TEST(ByteArrayTag, MoveAssignment)
{
    std::string name = "MoveAssignment";
    std::vector<int8_t> value = {-33, -11, 0, 11, 22, 33, 55};

    // Init A
    amc::ByteArrayTag tagA(name, value);
    ASSERT_STREQ(tagA.getName().c_str(), name.c_str());
    ASSERT_THAT(tagA.getValue(), testing::ElementsAreArray(value.begin(), value.end()));

    // Init B
    amc::ByteArrayTag tagB;
    ASSERT_STREQ(tagB.getName().c_str(), "");
    ASSERT_EQ(tagB.getValue().size(), 0);

    // Test Move Assignment
    tagB = std::move(tagA);
    EXPECT_STREQ(tagB.getName().c_str(), name.c_str());
    EXPECT_THAT(tagB.getValue(), testing::ElementsAreArray(value.begin(), value.end()));
}

TEST(ByteArrayTag, clone)
{
    amc::ByteArrayTag byteArrayTagA("Test1", {1, 2, 3});

    amc::ByteArrayTag *byteArrayTagB = tag_cast<amc::ByteArrayTag*>(byteArrayTagA.clone());
    EXPECT_TRUE(byteArrayTagA == *byteArrayTagB);

    delete byteArrayTagB;
}

TEST(ByteArrayTag, Equal)
{
    amc::ByteArrayTag byteArrayTagA("Test1", {1, 2, 3});
    amc::ByteArrayTag byteArrayTagB("Test1", {1, 2, 3});
    amc::ByteArrayTag byteArrayTagC("Test1", {1, 2, 3});
    amc::ByteArrayTag byteArrayTagD("Test2", {1, 2, 5});
    amc::ByteArrayTag byteArrayTagE;
    amc::EndTag endTag;

    EXPECT_TRUE(byteArrayTagA == byteArrayTagA);  // Test same object
    EXPECT_TRUE(byteArrayTagA == byteArrayTagB);  // Test same data #1
    EXPECT_TRUE(byteArrayTagA == byteArrayTagC);  // Test same data #2
    byteArrayTagB.setValue({1, 2, 5});
    EXPECT_FALSE(byteArrayTagA == byteArrayTagB); // Test different data #1
    byteArrayTagC.setName("Test3");
    EXPECT_FALSE(byteArrayTagA == byteArrayTagC); // Test different data #2

    EXPECT_FALSE(byteArrayTagE == endTag);   // Test different types
}

TEST(ByteArrayTag, NotEqual)
{
    amc::ByteArrayTag byteArrayTagA("Test1", {1, 2, 3});
    amc::ByteArrayTag byteArrayTagB("Test1", {1, 2, 3});
    amc::ByteArrayTag byteArrayTagC("Test1", {1, 2, 3});
    amc::ByteArrayTag byteArrayTagD("Test2", {1, 2, 5});
    amc::ByteArrayTag byteArrayTagE;
    amc::EndTag endTag;

    EXPECT_FALSE(byteArrayTagA != byteArrayTagA);  // Test same object
    EXPECT_FALSE(byteArrayTagA != byteArrayTagB);  // Test same data #1
    EXPECT_FALSE(byteArrayTagA != byteArrayTagC);  // Test same data #2
    byteArrayTagB.setValue({1, 2, 5});
    EXPECT_TRUE(byteArrayTagA != byteArrayTagB); // Test different data #1
    byteArrayTagC.setName("Test3");
    EXPECT_TRUE(byteArrayTagA != byteArrayTagC); // Test different data #2

    EXPECT_TRUE(byteArrayTagE != endTag);   // Test different types
}

TEST(ByteArrayTag, getType)
{
    amc::ByteArrayTag byteArrayTag;
    EXPECT_EQ(amc::TagType::ByteArray, byteArrayTag.getType());
}

TEST(ByteArrayTag, getData)
{
    const std::vector<unsigned char> testData = {
        0x07, 0x00, 0x0C, 0x62, 0x79, 0x74, 0x65, 0x41, 
        0x72, 0x72, 0x61, 0x79, 0x54, 0x61, 0x67, 0x00, 
        0x00, 0x00, 0x05, 0x80, 0xFB, 0x00, 0x05, 0x7F
    };

    amc::ByteArrayTag byteArrayTag("byteArrayTag", std::vector<int8_t>({-128, -5, 0, 5, 127}));
    std::vector<unsigned char> data = byteArrayTag.getData(false);

    EXPECT_EQ(data.size(), testData.size());
    EXPECT_THAT(data, ::testing::ElementsAreArray(testData));

    std::vector<unsigned char> data2 = byteArrayTag.getData(true);
    EXPECT_EQ(9, data2.size());
    EXPECT_THAT(data2, ::testing::ElementsAreArray(testData.begin() + 15, testData.end()));
}

TEST(ByteArrayTag, isEmpty)
{
    amc::ByteArrayTag byteArrayTagA;
    EXPECT_TRUE(byteArrayTagA.isEmpty());
    byteArrayTagA.pushBack(2);
    EXPECT_FALSE(byteArrayTagA.isEmpty());

    amc::ByteArrayTag byteArrayTagB("TestTag", {1, 2, 3});
    EXPECT_FALSE(byteArrayTagB.isEmpty());
}

TEST(ByteArrayTag, clear)
{
    amc::ByteArrayTag byteArrayTagB("TestTag", {1, 2, 3});
    EXPECT_FALSE(byteArrayTagB.isEmpty());
    byteArrayTagB.clear();
    EXPECT_TRUE(byteArrayTagB.isEmpty());
}

TEST(ByteArrayTag, erase)
{
    amc::ByteArrayTag byteArrayTagA("TestTag", {1, 2, 3});
    // Test index too high
    EXPECT_FALSE(byteArrayTagA.eraseAt(3));
    EXPECT_FALSE(byteArrayTagA.eraseAt(900));

    // successively erase first index until empty
    ASSERT_FALSE(byteArrayTagA.isEmpty());
    EXPECT_TRUE(byteArrayTagA.eraseAt(0));
    EXPECT_TRUE(byteArrayTagA.eraseAt(0));
    EXPECT_TRUE(byteArrayTagA.eraseAt(0));
    ASSERT_TRUE(byteArrayTagA.isEmpty());

    // Expect false, when trying to erase from empty ByteAraryTag
    EXPECT_FALSE(byteArrayTagA.eraseAt(0));

    // Erase from middle
    std::vector<int8_t> values1 = {1, 2, 3};
    std::vector<int8_t> values2 = {1, 3};
    amc::ByteArrayTag byteArrayTagB("TestTag", {1, 2, 3});
    ASSERT_EQ(3, byteArrayTagB.size());
    std::vector<int8_t> data1 = byteArrayTagB.getValue();
    EXPECT_THAT(data1, testing::ElementsAreArray(values1.begin(), values1.end()));
    byteArrayTagB.eraseAt(1);
    std::vector<int8_t> data2 = byteArrayTagB.getValue();
    ASSERT_EQ(2, byteArrayTagB.size());
    EXPECT_THAT(data2, testing::ElementsAreArray(values2.begin(), values2.end()));
}

TEST(ByteArrayTag, insert)
{
    // Insert into empty
    amc::ByteArrayTag byteArrayTagA;
    // Test invalid index
    ASSERT_EQ(0, byteArrayTagA.size());
    EXPECT_FALSE(byteArrayTagA.insert(1, 1));
    ASSERT_EQ(0, byteArrayTagA.size());

    // Test valid index - insert at end
    EXPECT_TRUE(byteArrayTagA.insert(0, 1));
    EXPECT_EQ(1, byteArrayTagA.size());

    // Insert in the middle
    std::vector<int8_t> values1 = {1, 2, 3};
    amc::ByteArrayTag byteArrayTagB("TestTag", {1, 3});
    ASSERT_EQ(2, byteArrayTagB.size());
    EXPECT_TRUE(byteArrayTagB.insert(1, 2));
    EXPECT_EQ(3, byteArrayTagB.size());
    std::vector<int8_t> data1 = byteArrayTagB.getValue();
    EXPECT_THAT(data1, testing::ElementsAreArray(values1.begin(), values1.end()));
}

TEST(ByteArrayTag, pushBack)
{
    amc::ByteArrayTag byteArrayTagA;
    EXPECT_EQ(0, byteArrayTagA.size());
    byteArrayTagA.pushBack(1);
    EXPECT_EQ(1, byteArrayTagA.at(0));
    EXPECT_EQ(1, byteArrayTagA.size());
    byteArrayTagA.pushBack(100);
    EXPECT_EQ(100, byteArrayTagA.at(1));
    EXPECT_EQ(2, byteArrayTagA.size());
}

TEST(ByteArrayTag, size)
{
    amc::ByteArrayTag byteArrayTagA;
    EXPECT_EQ(0, byteArrayTagA.size());

    amc::ByteArrayTag byteArrayTagB("TestTag", {1, 2, 3});
    EXPECT_EQ(3, byteArrayTagB.size());

    byteArrayTagB.clear();
    EXPECT_EQ(0, byteArrayTagB.size());
}

TEST(ByteArrayTag, at)
{
    const int8_t value1_in = -115;
    const int8_t value2_in = 0;
    const int8_t value3_in = 98;
    int8_t value1_out = 0;
    int8_t value2_out = 0;
    int8_t value3_out = 0;
    
    // Test copy
    amc::ByteArrayTag byteArrayTagA("TestTag", {value1_in, value2_in, value3_in});
    ASSERT_EQ(3, byteArrayTagA.size());
    value1_out = byteArrayTagA.at(0);
    EXPECT_EQ(value1_out, value1_in);
    value2_out = byteArrayTagA.at(1);
    EXPECT_EQ(value2_out, value2_in);
    value3_out = byteArrayTagA.at(2);
    EXPECT_EQ(value3_out, value3_in);

    // Test reference
    amc::ByteArrayTag byteArrayTagB("TestTag", {value1_in});
    ASSERT_EQ(1, byteArrayTagB.size());
    int8_t &value1_out_ref = byteArrayTagA.at(0);
    EXPECT_EQ(value1_out_ref, value1_in);
    value1_out_ref = value2_in;
    value1_out = byteArrayTagA.at(0);
    EXPECT_EQ(value1_out, value2_in);
}

TEST(ByteArrayTag, at_const)
{
    const int8_t value1_in = -115;
    const int8_t value2_in = 0;
    const int8_t value3_in = 98;

    // Test const copy
    const amc::ByteArrayTag byteArrayTagA("TestTag", {value1_in, value2_in, value3_in});
    ASSERT_EQ(3, byteArrayTagA.size());
    const int8_t value1_out = byteArrayTagA.at(0);
    EXPECT_EQ(value1_out, value1_in);
    const int8_t value2_out = byteArrayTagA.at(1);
    EXPECT_EQ(value2_out, value2_in);
    const int8_t value3_out = byteArrayTagA.at(2);
    EXPECT_EQ(value3_out, value3_in);
}

TEST(ByteArrayTag, getValue)
{
    std::vector<int8_t> value     = {1, 2, 3, 4};
    std::vector<int8_t> value2    = {1, 2, 3, 5};
    amc::ByteArrayTag byteArrayTag;

    std::vector<int8_t> data = byteArrayTag.getValue();
    EXPECT_EQ(0, data.size());
    byteArrayTag.setValue(value);
    std::vector<int8_t> data2 = byteArrayTag.getValue();
    ASSERT_THAT(data2, testing::ElementsAreArray(value.begin(), value.end()));
    byteArrayTag.setValue(value2);
    std::vector<int8_t> data3 = byteArrayTag.getValue();
    ASSERT_THAT(data3, testing::ElementsAreArray(value2.begin(), value2.end()));
}

TEST(ByteArrayTag, setValue)
{
    std::vector<int8_t> value = {1, 2, 3, 4};
    amc::ByteArrayTag byteArrayTag;
    EXPECT_EQ(0, byteArrayTag.size());
    byteArrayTag.setValue(value);
    EXPECT_EQ(4, byteArrayTag.size());
    std::vector<int8_t> data2 = byteArrayTag.getValue();
    ASSERT_THAT(data2, testing::ElementsAreArray(value.begin(), value.end()));
}

TEST(ByteArrayTag, tag_cast)
{
    amc::AbstractTag *testTag = new amc::ByteArrayTag("A", std::vector<int8_t>({1, 2, 3}));

    amc::ByteArrayTag *otherTag = tag_cast<amc::ByteArrayTag*>(testTag);
    EXPECT_EQ(otherTag, testTag);

    amc::IntTag *nullTag = tag_cast<amc::IntTag*>(testTag);
    EXPECT_EQ(nullTag, nullptr);

    delete testTag;
}